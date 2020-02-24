//
// Created by tony on 1/1/20.
//

#include <algorithm>
#include <SDL2/SDL_image.h>
#include "../header/Game.h"
#include "../header/Actor.h"
#include "../header/component/SpriteComponent.h"
#include "../header/component/BGSpriteComponent.h"
#include "../header/Ship.h"
#include "../header/component/TileMapComponent.h"
#include "../header/Asteroid.h"
#include "../header/component/CircleComponent.h"

Game::Game() {
    mIsRunning = true;
    mUpdatingActors = false;
    mTicks = 0;
}

bool Game::initialize() {
    int sdlInit = SDL_Init(SDL_INIT_VIDEO);
    if(sdlInit != 0) {
        SDL_Log("Cannot initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
            "Game Programming in C++ (Chapter 2)",
            100, //Top left X coordinate
            100, //Top left Y coordindate
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0 // no flags set
            );

    if(!mWindow) {
        SDL_Log("Cannot create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
            mWindow,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // Renderer flags
            );

    if(!mRenderer) {
        SDL_Log("Cannot create a renderer: %s", SDL_GetError());
        return false;
    }

    if(IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to initialize SDL png: %s", SDL_GetError());
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
    while(!mActors.empty()) {
        delete mActors.back();
    }
    while(!mPendingActors.empty()) {
        delete mPendingActors.back();
    }
    while(!mSprites.empty()) {
        delete mSprites.back();
    }

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    mIsRunning = false;
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


    //update asteroid collision
    for(int i = 0; i < mAsteroids.size(); i++) {
        for(int j = i + 1; j < mAsteroids.size(); j++) {
            if(intersect(mAsteroids[i]->getCircle(), mAsteroids[j])) {
                //mAsteroids[0]->reflect();
                //mAsteroids[1]->reflect();
            }
        }
    }

    for(auto asteroid : mAsteroids) {
        Vector2 pos = asteroid->getPosition();
        if (pos.x < 0 || pos.x > WINDOW_WIDTH) {
            asteroid->reflect(1, 0);
        } else if (pos.y < 0 || pos.y > WINDOW_HEIGHT) {

        }
    }

    //Delete all the dead actors
    for(auto deadActor : deadActors) {
        delete deadActor;
    }
}

void Game::generateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    // Draw all sprite components
    for (auto sprite : mSprites)
    {
        sprite->draw(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
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

SDL_Texture* Game::loadTexture(char *file) {
    SDL_Texture* tex = nullptr;
    // Is the texture already in the map?
    std::string fileName(file);
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end()) {
        tex = iter->second;
    }
    else {
        // Load from file
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if (!surf)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        // Create texture from surface
        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);
        if (!tex)
        {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }

        mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}

void Game::loadData() {
    // Create actor for the background (this doesn't need a subclass)
    Actor* temp = new Actor(this);
    temp->setPosition(Vector2(512.0f, 384.0f));
    // Create the "far back" background
    BGSpriteComponent* bg = new BGSpriteComponent(temp);
    bg->setScreenSize(Vector2(1024.0f, 768.0f));
    std::vector<SDL_Texture*> bgtexs = {
            loadTexture("Assets/Farback01.png"),
            loadTexture("Assets/Farback02.png")
    };
    bg->setBGTextures(bgtexs);
    bg->setScrollSpeed(-100.0f);
    //addSprite(bg);
    // Create the closer background
    bg = new BGSpriteComponent(temp, 50);
    bg->setScreenSize(Vector2(1024.0f, 768.0f));
    bgtexs = {
            loadTexture("Assets/Stars.png"),
            loadTexture("Assets/Stars.png")
    };
    bg->setBGTextures(bgtexs);
    bg->setScrollSpeed(-200.0f);

    int windowHeight;
    int windowWidth;

    SDL_GetWindowSize(mWindow, &windowWidth, &windowHeight);

    for(int i = 0; i < 10; i++) {
        auto* asteroid = new Asteroid(this);
        addActor(asteroid);
        mAsteroids.emplace_back(asteroid);
    }
}

void Game::addSprite(SpriteComponent *component) {
    //Find the insertion point for the new sprint
    //this would be the first element that has a higher insertion point that the new one.
    int drawOrder = component->getDrawOrder();
    auto itr = mSprites.begin();
    for(;itr != mSprites.end(); itr++) {
        if(drawOrder < (*itr)->getDrawOrder()) {
            break;
        }
    }
    mSprites.insert(itr, component);
}

void Game::removeSprite(SpriteComponent* component) {
    mSprites.erase(std::remove(mSprites.begin(), mSprites.end(), component), mSprites.end());
}

void Game::unloadData() {
    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    // Destroy textures
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}
