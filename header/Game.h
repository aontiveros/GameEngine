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

//forward declaration
class Actor;
class SpriteComponent;
class Ship;
class MoveComponent;
class Asteroid;
class Texture;
class Shader;
class Renderer;

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

    Texture *loadTexture(const std::string& fileName);


private:
    void processInput();
    void updateGame();
    void generateOutput();
    void loadData();
    void unloadData();
    bool loadShaders();

    bool mIsRunning;
    Uint32 mTicks;

    //Actors
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    Ship* mShip;

    bool mUpdatingActors;

    const float WINDOW_HEIGHT = 768;
    const float WINDOW_WIDTH = 1024;

    float mRed = 0.0f;
    float mGreen = 0.0f;
    float mBlue = 0.0f;
    bool direction = true;

    Renderer* mRenderer;
};


#endif //CHAPTER2_GAME_H
