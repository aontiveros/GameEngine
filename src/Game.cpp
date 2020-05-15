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
    //Set the core openGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE);
    //Specify openGL version 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    //Request a color buffer with 8-bits per channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    //Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //Force openGL to utilize hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    //Create window
    mWindow = SDL_CreateWindow("OpenGL Game", 100, 100, 1024, 768, SDL_WINDOW_OPENGL);

    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    //Grab the context for openGL
    mContext = SDL_GL_CreateContext(mWindow);

    //Configure backwards compatibility with openGL
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        SDL_Log("Failed to initialize GLEW");
        return false;
    }
    //It is possible for there to be a benign failure. This next line clears it out.
    glGetError();

    if(!loadShaders()) {
        SDL_Log("Failed to load shaders.");
        return false;
    }

    initSpriteVerts();

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

    while(!mActors.empty()) {
        delete mActors.back();
    }
    while(!mPendingActors.empty()) {
        delete mPendingActors.back();
    }
    while(!mSprites.empty()) {
        delete mSprites.back();
    }

    delete mSpriteVerts;
    mSpriteShader->unload();
    delete mSpriteShader;

    SDL_GL_DeleteContext(mContext);
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

    //update background colpr
    if(mBlue >= 1.0f) {
        direction = false;
        mBlue = 1.0f;
    } else if(mBlue <= 0.0f) {
        direction = true;
        mBlue = 0.0f;
    }
    if(direction) {
        mBlue += .01f;
    } else {
        mBlue -= .01f;
    }

}

void Game::generateOutput() {
    // Set the color to grey
    glClearColor(mRed, mGreen, mBlue, 1.0f);
    //clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw all sprite components
    // Enable alpha blending on the color buffer
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set the shader / vertices as active
    mSpriteShader->setActive();
    mSpriteVerts->setActive();

    // Draw all out sprites
    for(auto sprite : mSprites) {
        sprite->draw(mSpriteShader);
    }

    //Swap the buffers, which also displays the scene
    SDL_GL_SwapWindow(mWindow);
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
    Texture* tex = nullptr;
    // Is the texture already in the map?
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end()) {
        tex = iter->second;
    } else {
        // Load from file
        tex = new Texture();
        if (!tex->load(fileName)) {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            delete tex;
            return nullptr;
        }
        mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
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
    while (!mActors.empty()) {
        delete mActors.back();
    }

    // Destroy textures
    for (auto i : mTextures) {
        delete i.second;
    }
    mTextures.clear();
}

void Game::initSpriteVerts() {
    float vertexBuffer[] = {
            -0.5f,  0.5f, 0.f, 0.f, 0.f, 0.0f, 0.0f, 0.0f,// top left
            0.5f,  0.5f, 0.f, 1.f, 0.f,  0.0f, 0.0f, 0.0f, // top right
            0.5f, -0.5f, 0.f, 1.f, 1.f,  0.0f, 0.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.f, 0.f, 1.f,  0.0f, 0.0f, 0.0f // bottom left
    };

    unsigned int indexBuffer[] = {
            0, 1, 2,
            2, 3, 0
    };
    mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
}

bool Game::loadShaders() {
    mSpriteShader = new Shader();
    if(!mSpriteShader->load("Shaders/Sprite.vert", "Shaders/Sprite.frag")) {
        return false;
    }
    mSpriteShader->setActive();
    Matrix4 viewProjection = Matrix4::CreateSimpleViewProj(1024.0f, 768.0f);
    mSpriteShader->setMatrixUniform("uViewProj", viewProjection);
    return true;
}
