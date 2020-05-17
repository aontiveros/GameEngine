//
// Created by tony on 5/10/20.
//

#include "../../header/graphics/Renderer.h"
#include "../../header/actor/Ship.h"
#include "../../header/component/SpriteComponent.h"
#include "../../header/graphics/VertexArray.h"
#include "../../header/graphics/Texture.h"
#include "../../header/graphics/Mesh.h"
#include "../../header/graphics/Shader.h"

#include <algorithm>
#include <GL/glew.h>
#include <SDL_image.h>


Renderer::Renderer(Game *game) : mGame(game) {
}

Renderer::~Renderer() {

}

bool Renderer::initialize(float screenWidth, float screenHeight) {
    mScreenHeight = screenHeight;
    mScreenWidth = screenWidth;
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
    mWindow = SDL_CreateWindow("OpenGL Game", 100, 100, mScreenWidth, mScreenHeight, SDL_WINDOW_OPENGL);

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

    createSpriteVerts();

    loadData();

    mTicks = SDL_GetTicks();

    return true;
}

void Renderer::draw() {

}

bool Renderer::loadShaders() {

}

void Renderer::shutdown() {
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
}
void Renderer::unloadData() {

}

void Renderer::addSprite(SpriteComponent *sprite) {
    mSprites.emplace_back(sprite);
}

void Renderer::remoteSprite(SpriteComponent *sprite) {
    mSprites.erase(std::remove(mSprites.begin(), mSprites.end(), sprite), mSprites.end());
}

Texture * Renderer::getTexture(const std::string &fileName) {
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

Mesh * Renderer::getMesh(const std::string &fileName) {
    Mesh* rMesh = nullptr;
    auto itr = mMeshes.find(fileName);
    if(itr != mMeshes.end()) {
        rMesh = itr->second;
    } else {
        rMesh = new Mesh();
        if(rMesh->load(fileName, mGame)) {
            mMeshes.emplace(fileName, rMesh);
            return rMesh;
        } else {
            SDL_Log("Failed to load mesh file %s", fileName.c_str());
            delete rMesh;
            rMesh = nullptr;
        }
    }
    return rMesh;
}

void Renderer::createSpriteVerts() {
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

void Renderer::loadData() {
    // Create player's ship
//    mShip = new Ship(this);
//    Quaternion q(Vector3::UnitY, -Math::PiOver2);
//    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
//    mShip->setRotation(q);
//
//    // Create asteroids
//    const int numAsteroids = 20;
//    for (int i = 0; i < numAsteroids; i++)
//    {
//        new Asteroid(this);
//    }
}
