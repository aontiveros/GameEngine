//
// Created by tony on 1/14/20.
//

#include "../../header/component/MoveComponent.h"
#include "../../header/Actor.h"
#include "../../header/Math.h"

MoveComponent::MoveComponent(Actor *actor, int updateOwner) : Component(actor, updateOwner) {

}

void MoveComponent::update(float deltaTime) {
    if(!Math::NearZero(mAngularSpeed)) {
        float rot = getActor()->getRotation();
        rot += mAngularSpeed * deltaTime;
        getActor()->setRotation(rot);
    }
    if(!Math::NearZero(mForwardSpeed)) {
        Vector2 pos = getActor()->getPosition();
        pos += getActor()->getForward() * mForwardSpeed * deltaTime;
        getActor()->setPosition(pos);
    }
}
