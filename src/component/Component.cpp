//
// Created by tony on 1/1/20.
//

#include "component/Component.h"
#include "actor/Actor.h"

Component::Component(Actor *actor, int updateOrder) {
    mActor = actor;
    mActor->addComponent(this);
    mUpdateOrder = updateOrder;
}

Component::~Component() {
    mActor->removeComponent(this);
}

void Component::update(float deltaTime) {

}

void Component::processInput(const uint8_t *keyState) {

}
