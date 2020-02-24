//
// Created by tony on 1/3/20.
//

#ifndef CHAPTER2_TILEMAPCOMPONENT_H
#define CHAPTER2_TILEMAPCOMPONENT_H

#include <string>
#include <vector>

#include "SpriteComponent.h"

class TileMapComponent : public SpriteComponent {
public:
    TileMapComponent(int windowWidth, int windowHeight, Actor* actor, int drawOrder = 10);

    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;


    void setTileMapResource(std::string fileName);

private:

    void loadCSVFromResource();
    //Texture
    std::vector<int> mTileMap;
    std::string mFileName;

    int mWindowWidth;
    int mWindowHeight;

    const int TILE_WIDTH = 32;
    const int TILE_HEIGHT = 32;
};


#endif //CHAPTER2_TILEMAPCOMPONENT_H
