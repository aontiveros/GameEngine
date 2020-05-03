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
    actor->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent() {
    getActor()->getGame()->removeSprite(this);
}

void SpriteComponent::draw(Shader *shader) {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::setTexture(SDL_Texture *texture) {
    mTexture = texture;
    // Set width/height
}


