//
// Created by tony on 1/1/20.
//

#ifndef CHAPTER2_ANIMSPRITECOMPONENT_H
#define CHAPTER2_ANIMSPRITECOMPONENT_H

#include <vector>
#include "SpriteComponent.h"


//forward declaration
class Actor;
class Texture;

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(Actor* actor, int drawOrder = 100);

    void update(float deltaTime) override;
    // Set the textures used for animation
    void setAnimationTextures(const std::vector<Texture*>& textures);

    // get/set the animation fps
    float getAnimationFps() const { return mAnimationFps; }
    void setAnimationFps(float fps) { mAnimationFps = fps; }

private:
    //All textures
    std::vector<Texture*> mAnimationTextures;
    //Current frame displayed
    float mCurrentFrame;
    // Animation frame rate
    float mAnimationFps;

};


#endif //CHAPTER2_ANIMSPRITECOMPONENT_H
