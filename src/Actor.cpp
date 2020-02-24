//
// Created by tony on 1/1/20.
//
#include <algorithm>

#include "../header/Actor.h"
#include "../header/component/Component.h"
#include "../header/Game.h"

Actor::Actor(Game* game) {
    mState = Actor::EActive;
    mPosition = Vector2::Zero;
    mScale = 1.0f;
    mRotation = 0.0f;
    mGame = game;
}

Actor::~Actor() {
    mGame->removeActor(this);
    while(!mComponents.empty()) {
        delete mComponents.back();
    }
}

void Actor::update(float deltaTime) {
    if (mState == EActive)
    {
        updateComponents(deltaTime);
        updateActor(deltaTime);
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

void Actor::setPosition(Vector2 position) {
    mPosition.x = position.x;
    mPosition.y = position.y;
}
