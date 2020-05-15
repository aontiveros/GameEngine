//
// Created by tony on 1/1/20.
//

#include "../../header/component/Component.h"
#include "../../header/actor/Actor.h"

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
