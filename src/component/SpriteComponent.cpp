//
// Created by tony on 1/1/20.
//

#include <iostream>
#include "../../header/component/SpriteComponent.h"
#include "../../header/Game.h"
#include "../../header/actor/Actor.h"
#include "../../header/Math.h"
#include "../../header/graphics/Shader.h"
#include "../../header/graphics/Texture.h"


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
    Matrix4 scaleMat = Matrix4::CreateScale(
            static_cast<float>(mTextureWidth),
            static_cast<float>(mTextureHeight),
            1.0f
            );
    Matrix4 world = scaleMat * getActor()->getWorldTransform();
    // Set the world transform
    shader->setMatrixUniform("uWorldTransform", world);
    mTexture->setActive();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void SpriteComponent::setTexture(Texture *texture) {
    mTexture = texture;
    // Set width/height
    // Set width/height
    mTextureHeight = texture->getHeight();
    mTextureWidth = texture->getWidth();
}


