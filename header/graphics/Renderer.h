//
// Created by tony on 5/10/20.
//

#ifndef CHAPTER2_RENDERER_H
#define CHAPTER2_RENDERER_H

#include <string>
#include <unordered_map>
#include <SDL_video.h>
#include <vector>

//forward declares
class SpriteComponent;
class Texture;
class Mesh;
class Game;
class Shader;
class VertexArray;
class Actor;

class Renderer {
private:
    Renderer(Game* game);
    ~Renderer();
    // Initialize and shutdown the renderer
    bool initialize(float screenWidth, float screenHeight);
    void shutdown();
    // Unload all the textures/meshes
    void unloadData();
    // Draw the frame
    void draw();
    void addSprite(SpriteComponent* sprite);
    void remoteSprite(SpriteComponent* sprite);
    Texture* getTexture(const std::string& fileName);
    Mesh* getMesh(const std::string& fileName);

private:
    bool loadShaders();
    void createSpriteVerts();
    void loadData();

    Game* mGame;
    float mScreenWidth;
    float mScreenHeight;
    std::unordered_map<std::string, Texture*> mTextures;
    std::unordered_map<std::string, Mesh*> mMeshes;

    SDL_Window* mWindow;
    SDL_GLContext mContext;
    Uint32 mTicks;

    //Sprite vert
    VertexArray* mSpriteVerts = nullptr;
    Shader* mSpriteShader;

    bool mUpdatingActors;

    //Actors
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;

    //Components
    std::vector<SpriteComponent*> mSprites;
//    std::vector<Asteroid*> mAsteroids;
//    Ship* mShip;

};


#endif //CHAPTER2_RENDERER_H
