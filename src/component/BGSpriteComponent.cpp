//
// Created by tony on 1/1/20.
//

#include "component/BGSpriteComponent.h"
#include "actor/Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor *actor, int drawOrder) : SpriteComponent(actor, drawOrder) {
    mScrollSpeed = 0.0f;
}

void BGSpriteComponent::update(float deltaTime) {
    SpriteComponent::update(deltaTime);
    for(auto& bg : mBGTextures) {
        //Update the x offset
        bg.mOffset.x += mScrollSpeed * deltaTime;
        // If this is completely off screen, reset it to the right of the last bg texture
        if(bg.mOffset.x < -mScreenSize.x) {
            bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
        }
    }
}

void BGSpriteComponent::draw(Shader* shader) {
//    for(auto& bg : mBGTextures) {
//        SDL_Rect rect;
//
//        rect.w = static_cast<int>(mScreenSize.x);
//        rect.h = static_cast<int>(mScreenSize.y);
//
//        rect.x = static_cast<int>(getActor()->getPosition().x - rect.w / 2 + bg.mOffset.x);
//        rect.y = static_cast<int>(getActor()->getPosition().y - rect.h / 2 + bg.mOffset.y);
//
//        SDL_RenderCopy(
//                renderer,
//                bg.mTexture,
//                nullptr,
//                &rect
//                );
//    }
    SpriteComponent::draw(shader);
}

void BGSpriteComponent::setBGTextures(const std::vector<SDL_Texture *> &textures) {
    int count = 0;
    for(auto& bgTexture : textures) {
        BGTexture temp;
        temp.mTexture = bgTexture;
        //Each texture is screen width in offset
        temp.mOffset.x = count * mScreenSize.x;
        temp.mOffset.y = 0.0f;
        mBGTextures.emplace_back(temp);
        count++;
    }
}
