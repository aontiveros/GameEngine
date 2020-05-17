//
// Created by tony on 1/1/20.
//

#include <algorithm>
#include <GL/glew.h>
#include <SDL_image.h>
#include "../header/Game.h"
#include "../header/actor/Actor.h"
#include "../header/component/SpriteComponent.h"
#include "../header/component/BGSpriteComponent.h"
#include "../header/actor/Ship.h"
#include "../header/component/TileMapComponent.h"
#include "../header/actor/Asteroid.h"
#include "../header/component/CircleComponent.h"
#include "../header/graphics/Texture.h"
#include "../header/graphics/Shader.h"
#include "../header/graphics/Renderer.h"


Game::Game() {
    mIsRunning = true;
    mUpdatingActors = false;
    mTicks = 0;
}

bool Game::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    mRenderer = new Renderer(this);
    if(!mRenderer->initialize(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        SDL_Log("Failed to initialize renderer.");
        delete mRenderer;
        mRenderer = nullptr;
        return false;
    }
    loadData();
    mTicks = SDL_GetTicks();
    return true;
}

void Game::runLoop() {
    while (mIsRunning) {
        processInput();
        updateGame();
        generateOutput();
    }
}

void Game::shutdown() {
    unloadData();
    if (mRenderer) {
        mRenderer->shutdown();
    }
    mIsRunning = false;
    SDL_Quit();
}

void Game::processInput() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT :
                mIsRunning = false;
                break;
        }
    }

    //Get the state of the keyboard
    const Uint8* keyEvent = SDL_GetKeyboardState(nullptr);
    if(keyEvent[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
}

void Game::updateGame() {
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicks + 16));
        //get delta time
    float deltaTime = static_cast<float>(SDL_GetTicks() - mTicks) / 1000.0f;

    //update tick count
    mTicks = SDL_GetTicks();

    //guard against concurrent modifications to actors.
    mUpdatingActors = true;
    for(auto actor : mActors) {
        actor->update(deltaTime);
    }
    mUpdatingActors = false;

    //Move any pending actors to actors
    for(auto pendingActor : mPendingActors) {
        //Perform a world transform in the same frame that they are created.
        pendingActor->computeWorldTransform();
        mActors.emplace_back(pendingActor);
    }
    mPendingActors.clear();

    //Add any dead actors to a temp vector
    std::vector<Actor*> deadActors;

    for(auto actor : mActors) {
        if(actor->getState() == Actor::EDead) {
            deadActors.emplace_back(actor);
        }
    }

    //Delete all the dead actors
    for(auto deadActor : deadActors) {
        delete deadActor;
    }
}

void Game::generateOutput() {
    mRenderer->draw();
}

void Game::addActor(Actor* actor) {
    if(mUpdatingActors) {
        mPendingActors.emplace_back(actor);
    } else {
        mActors.emplace_back(actor);
    }
}

void Game::removeActor(Actor *actor) {
    mActors.erase(std::remove(mActors.begin(), mActors.end(), actor), mActors.end());
    mPendingActors.erase(std::remove(mPendingActors.begin(), mPendingActors.end(), actor), mPendingActors.end());
}

Texture* Game::loadTexture(const std::string& fileName) {
    return mRenderer->getTexture(fileName);
}

void Game::loadData() {
    // Create player's ship
    mShip = new Ship(this);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
    mShip->setRotation(q);

    // Create asteroids
    const int numAsteroids = 20;
    for (int i = 0; i < numAsteroids; i++)
    {
        new Asteroid(this);
    }
}

void Game::addSprite(SpriteComponent *component) {
    mRenderer->addSprite(component);
}

void Game::removeSprite(SpriteComponent* component) {
    mRenderer->remoteSprite(component);
}

void Game::unloadData() {
    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!mActors.empty()) {
        delete mActors.back();
    }

    if (mRenderer) {
        mRenderer->unloadData();
    }
}
