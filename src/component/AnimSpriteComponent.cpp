//
// Created by tony on 1/1/20.
//

#include "../../header/component/AnimSpriteComponent.h"

AnimSpriteComponent::AnimSpriteComponent(Actor *actor, int drawOrder) : SpriteComponent(actor, drawOrder) {
    mCurrentFrame = 0.0f;
    mAnimationFps = 24.0f;
}

void AnimSpriteComponent::update(float deltaTime) {
    SpriteComponent::update(deltaTime);

    if(!mAnimationTextures.empty()) {
        //update the frame based on the current framerate
        mCurrentFrame += mAnimationFps * deltaTime;

        //Wrap the current frame if needed
        while(mCurrentFrame >= mAnimationTextures.size()) {
            mCurrentFrame -= mAnimationTextures.size();
        }

        setTexture(mAnimationTextures[static_cast<int>(mCurrentFrame)]);
    }
}

void AnimSpriteComponent::setAnimationTextures(const std::vector<SDL_Texture*>& textures) {
    mAnimationTextures = textures;
    if(!mAnimationTextures.empty()) {
        mCurrentFrame = 0.0f;
        setTexture(mAnimationTextures[static_cast<int>(mCurrentFrame)]);
    }
}
