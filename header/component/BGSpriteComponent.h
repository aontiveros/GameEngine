//
// Created by tony on 1/1/20.
//

#ifndef CHAPTER2_BGSPRITECOMPONENT_H
#define CHAPTER2_BGSPRITECOMPONENT_H

#include <vector>
#include "SpriteComponent.h"
#include "../Math.h"

//forward declaration
class Actor;

class BGSpriteComponent : public SpriteComponent {
public:
    BGSpriteComponent(Actor* actor, int drawOrder = 10);
    //update/draw overrides
    void update(float deltaTime) override;
    void draw(SDL_Renderer* renderer) override;

    //Set the textures used for the background
    void setBGTextures(const std::vector<SDL_Texture*>& textures);
    // get/set the scroll speed of BG
    void setScreenSize(const Vector2& size) { mScreenSize = size;}
    void setScrollSpeed(float scrollSpeed) {mScrollSpeed = scrollSpeed;}
    float getScrollSpeed() { return mScrollSpeed; }

private:
    struct BGTexture {
        SDL_Texture* mTexture;
        Vector2 mOffset;
    };
    std::vector<BGTexture> mBGTextures;
    float mScrollSpeed;
    Vector2 mScreenSize;

};


#endif //CHAPTER2_BGSPRITECOMPONENT_H
