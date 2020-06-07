//
// Created by tony on 1/1/20.
//

#include <iostream>
#include "component/SpriteComponent.h"
#include "Game.h"
#include "actor/Actor.h"
#include "Math.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"


SpriteComponent::SpriteComponent(Actor *actor, int drawOrder) : Component(actor) {
    mDrawOrder = drawOrder;
    mTexture = nullptr;
    mTextureWidth = 0;
    mTextureHeight = 0;
    actor->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent() {
    getActor()->getGame()->removeSprite(this);
}

void SpriteComponent::draw(Shader *shader) {
    if(mTexture != nullptr) {
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
}

void SpriteComponent::setTexture(Texture *texture) {
    mTexture = texture;
    // Set width/height
    // Set width/height
    mTextureHeight = texture->getHeight();
    mTextureWidth = texture->getWidth();
}


