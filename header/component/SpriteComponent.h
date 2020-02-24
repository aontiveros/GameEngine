//
// Created by tony on 1/1/20.
//

#ifndef CHAPTER2_SPRITECOMPONENT_H
#define CHAPTER2_SPRITECOMPONENT_H

#include <SDL_system.h>
#include "Component.h"

//forward declaration
class Actor;

class SpriteComponent : public Component{
public:
    SpriteComponent(Actor* actor, int drawOrder = 100);
    ~SpriteComponent();

    virtual void draw(SDL_Renderer* renderer);
    virtual void setTexture(SDL_Texture* texture);

    int getDrawOrder() { return mDrawOrder; }
    SDL_Texture* getTexture(){ return mTexture; }


private:
    //Texture to draw
    SDL_Texture* mTexture;

    //Draw order used for painter's algorithm
    int mDrawOrder;
    //width/length of the texture
    int mTextureWidth;
    int mTextureHeight;
};


#endif //CHAPTER2_SPRITECOMPONENT_H
