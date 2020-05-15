//
// Created by tony on 5/10/20.
//

#ifndef CHAPTER2_RENDERER_H
#define CHAPTER2_RENDERER_H

#include <string>
#include <unordered_map>

//forward declares
class SpriteComponent;
class Texture;
class Mesh;

class Renderer {
private:
    Renderer();
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
    void createVerts();

    float mScreenWidth;
    float mScreenHeight;
    std::unordered_map<std::string, Texture*> mTextures;
    std::unordered_map<std::string, Mesh*> mMeshes;
};


#endif //CHAPTER2_RENDERER_H
