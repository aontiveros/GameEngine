//
// Created by tony on 1/1/20.
//

#ifndef CHAPTER2_GAME_H
#define CHAPTER2_GAME_H

#include <SDL.h>
#include <SDL_video.h>
#include <vector>
#include <unordered_map>
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"

//forward declaration
class Actor;
class SpriteComponent;
class Ship;
class MoveComponent;
class Asteroid;

class Game {
public:
    Game();
    bool initialize();
    void runLoop();
    void shutdown();

    void addActor(Actor* actor);
    void removeActor(Actor* actor);

    void addSprite(SpriteComponent* component);
    void removeSprite(SpriteComponent* component);

    SDL_Texture *loadTexture(char *file);


private:
    void processInput();
    void updateGame();
    void generateOutput();
    void loadData();
    void unloadData();
    void initSpriteVerts();
    bool loadShaders();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    SDL_GLContext mContext;
    bool mIsRunning;
    Uint32 mTicks;

    //Actors
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;

    //Components
    std::vector<SpriteComponent*> mSprites;
    std::vector<Asteroid*> mAsteroids;
    Ship* mShip;

    //Sprite vert
    VertexArray* mSpriteVerts = nullptr;
    Shader* mSpriteShader;

    bool mUpdatingActors;

    // Map of textures loaded
    std::unordered_map<std::string, SDL_Texture*> mTextures;

    const int WINDOW_HEIGHT = 768;
    const int WINDOW_WIDTH = 1024;

};


#endif //CHAPTER2_GAME_H
