//
// Created by tony on 1/3/20.
//
#include <fstream>
#include <SDL_log.h>

#include "../../header/component/Component.h"

#include "../../header/component/TileMapComponent.h"


TileMapComponent::TileMapComponent(int windowWidth, int windowHeight, Actor *actor, int drawOrder) : SpriteComponent(actor, drawOrder) {
    mFileName = "";
    mWindowHeight = windowHeight;
    mWindowWidth = windowWidth;
}

void TileMapComponent::update(float deltaTime) {
    SpriteComponent::update(deltaTime);
}

void TileMapComponent::setTileMapResource(std::string fileName) {
    mFileName = fileName;
    loadCSVFromResource();
}

void TileMapComponent::loadCSVFromResource() {
    std::ifstream file(mFileName);
    mTileMap.clear();
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            int start = 0;
            int idx = 0;
            while(idx <= line.size()) {
                if(idx == line.size() ||
                        line[idx] == ',') {
                    mTileMap.emplace_back(std::stoi(line.substr(start, idx - start)));
                    start = idx + 1;
                }
                idx++;
            }
        }
        file.close();
    } else {
        SDL_Log("Cannot process tile map from file: %s", mFileName.c_str());
    }
}

void TileMapComponent::draw(Shader *shader) {
    SpriteComponent::draw(shader);
//    if(getTexture() != nullptr) {
//        int col = 8;
//        int tilesPerRow = 32;
//        int tileRows = 24;
//        int tileWidth = mWindowWidth / 32;
//        int tileHeight = mWindowHeight / 24;
//        for(int i = 0; i < tileRows; i++) {
//            for(int j = 0; j < tilesPerRow; j++) {
//                int tile = mTileMap[(i * tilesPerRow) + j];
//                if(tile != -1) {
//                    int tileX = tile % col * 32;
//                    int tileY = tile / col * 32;
//                    SDL_Rect tileRect;
//                    tileRect.w = 32;
//                    tileRect.h = 32;
//                    tileRect.x = tileX;
//                    tileRect.y = tileY;
//
//                    SDL_Rect screenRect;
//                    screenRect.h = tileHeight;
//                    screenRect.w = tileWidth;
//
//                    screenRect.x = j * tileWidth;
//                    screenRect.y = i * tileHeight;
//
//                    SDL_RenderCopyEx(
//                            renderer,
//                            getTexture(),
//                            &tileRect,
//                            &screenRect,
//                            0,
//                            nullptr,
//                            SDL_FLIP_NONE
//                    );
//                }
//            }
//        }
//    } else {
//        SDL_Log("Cannot draw tile map as there is no texture");
//    }
}
