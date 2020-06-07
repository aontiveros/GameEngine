//
// Created by tony on 1/1/20.
//
#include <algorithm>

#include "actor/Actor.h"
#include "component/Component.h"
#include "Game.h"

Actor::Actor(Game* game) {
    mState = Actor::EActive;
    mPosition = Vector3::Zero;
    mScale = 1.0f;
    mRotation = Quaternion::Identity;
    mGame = game;
    game->addActor(this);
    mRecomputeWorldTransform = true;
}

Actor::~Actor() {
    mGame->removeActor(this);
    while(!mComponents.empty()) {
        delete mComponents.back();
    }
}

void Actor::update(float deltaTime) {
    if (mState == EActive) {
        computeWorldTransform();

        updateComponents(deltaTime);
        updateActor(deltaTime);

        computeWorldTransform();
    }
}

void Actor::updateComponents(float deltaTime) {
    for(auto component : mComponents) {
        component->update(deltaTime);
    }
}

void Actor::updateActor(float deltaTime) {

}

void Actor::removeComponent(Component *component) {
    mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), component), mComponents.end());
}

void Actor::addComponent(Component *component) {
    int updateOrder = component->getUpdateOrder();
    auto itr = mComponents.begin();
    for(; itr != mComponents.end(); itr++) {
        if((*itr)->getUpdateOrder() < updateOrder) {
            break;
        }
    }
    mComponents.insert(itr, component);
}

void Actor::computeWorldTransform() {
    if(mRecomputeWorldTransform) {
        mRecomputeWorldTransform = false;
        //Scale -> Rotate -> Translate
        mWorldTransform = Matrix4::CreateScale(mScale);
        mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
        mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, mPosition.z));

        //Inform components that a world transform was done.
        for(auto component : mComponents) {
            component->onUpdateWorldTransform();
        }
    }
}

void Actor::setPosition(Vector3 position) {
    mPosition.x = position.x;
    mPosition.y = position.y;
    mPosition.z = position.z;
    mRecomputeWorldTransform = true;
}

void Actor::setRotation(Quaternion rotation) {
    mRotation.x = rotation.x;
    mRotation.y = rotation.y;
    mRotation.z = rotation.z;
    mRotation.w = rotation.w;
    mRecomputeWorldTransform = true;
}

void Actor::setScale(float scale) {
    mScale = scale;
    mRecomputeWorldTransform = true;
}

void Actor::processInput(const uint8_t* keyState) {
     if (mState == EActive) {
         for (auto& comp : mComponents) {
             comp->processInput(keyState);
         }
         actorInput(keyState);
     }
}

void Actor::actorInput(const uint8_t* keyState) {

}


