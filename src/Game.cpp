//
// Created by tony on 1/1/20.
//

#include <algorithm>
#include <GL/glew.h>
#include <SDL_image.h>
#include "Game.h"
#include "actor/Actor.h"
#include "component/SpriteComponent.h"
#include "component/BGSpriteComponent.h"
#include "actor/Ship.h"
#include "component/TileMapComponent.h"
#include "actor/Asteroid.h"
#include "component/CircleComponent.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/Renderer.h"
#include "component/MeshComponent.h"
#include "actor/PlaneActor.h"
#include "actor/CameraActor.h"


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
    // Create actors
    Actor* a = new Actor(this);
    a->setPosition(Vector3(200.0f, 75.0f, 0.0f));
    a->setScale(100.0f);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
    a->setRotation(q);
    MeshComponent* mc = new MeshComponent(a);
    mc->setMesh(mRenderer->getMesh("Assets/Cube.gpmesh"));

    a = new Actor(this);
    a->setPosition(Vector3(200.0f, -75.0f, 0.0f));
    a->setScale(3.0f);
    mc = new MeshComponent(a);
    mc->setMesh(mRenderer->getMesh("Assets/Sphere.gpmesh"));

    // Setup floor
    const float start = -1250.0f;
    const float size = 250.0f;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            a = new PlaneActor(this);
            a->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
        }
    }

    // Left/right walls
    q = Quaternion(Vector3::UnitX, Math::PiOver2);
    for (int i = 0; i < 10; i++)
    {
        a = new PlaneActor(this);
        a->setPosition(Vector3(start + i * size, start - size, 0.0f));
        a->setRotation(q);

        a = new PlaneActor(this);
        a->setPosition(Vector3(start + i * size, -start + size, 0.0f));
        a->setRotation(q);
    }

    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
    // Forward/back walls
    for (int i = 0; i < 10; i++)
    {
        a = new PlaneActor(this);
        a->setPosition(Vector3(start - size, start + i * size, 0.0f));
        a->setRotation(q);

        a = new PlaneActor(this);
        a->setPosition(Vector3(-start + size, start + i * size, 0.0f));
        a->setRotation(q);
    }

    // Setup lights
    mRenderer->setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
    DirectionalLight& dir = mRenderer->getDirectionalLight();
    dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
    dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

    // Camera actor
    mCameraActor = new CameraActor(this);

    // UI elements
    a = new Actor(this);
    a->setPosition(Vector3(-350.0f, -350.0f, 0.0f));
    SpriteComponent* sc = new SpriteComponent(a);
    sc->setTexture(mRenderer->getTexture("Assets/HealthBar.png"));

    a = new Actor(this);
    a->setPosition(Vector3(375.0f, -275.0f, 0.0f));
    a->setScale(0.75f);
    sc = new SpriteComponent(a);
    sc->setTexture(mRenderer->getTexture("Assets/Radar.png"));
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
