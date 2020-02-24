//
// Created by tony on 1/1/20.
//

#include "../../header/component/SpriteComponent.h"
#include "../../header/Game.h"
#include "../../header/Actor.h"
#include "../../header/Math.h"


SpriteComponent::SpriteComponent(Actor *actor, int drawOrder) : Component(actor) {
    mDrawOrder = drawOrder;
    mTextureWidth = 0;
    mTextureHeight = 0;
}

SpriteComponent::~SpriteComponent() {
    getActor()->getGame()->removeSprite(this);
}

void SpriteComponent::draw(SDL_Renderer *renderer) {
    if(mTexture) {
         SDL_Rect rect;
         rect.w = static_cast<int>(mTextureWidth * getActor()->getScale());
         rect.h = static_cast<int>(mTextureHeight * getActor()->getScale());

         rect.x = static_cast<int>(getActor()->getPosition().x - rect.w / 2);
         rect.y = static_cast<int>(getActor()->getPosition().y - rect.h / 2);

         SDL_RenderCopyEx(
                 renderer,
                 mTexture,
                 nullptr,
                 &rect,
                 -Math::ToDegrees(getActor()->getRotation()),
                 nullptr,
                 SDL_FLIP_NONE
                 );
    }
}

void SpriteComponent::setTexture(SDL_Texture *texture) {
    mTexture = texture;

    SDL_QueryTexture(
            mTexture,
            nullptr,
            nullptr,
            &mTextureWidth,
            &mTextureHeight
            );
}


