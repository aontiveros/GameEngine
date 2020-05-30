//
// Created by tony on 1/14/20.
//

#include "component/MoveComponent.h"
#include "actor/Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor *actor, int updateOwner) : Component(actor, updateOwner) {

}

void MoveComponent::update(float deltaTime) {
    if(!Math::NearZero(mAngularSpeed)) {
        Quaternion rot = getActor()->getRotation();
        float angle = mAngularSpeed * deltaTime;
        // Create a quaternion for incremental rotation
        // (Rotate about the axis)
        Quaternion inc(Vector3::UnitX, angle);
        // Concat old quaternion to old quaternion
        rot = Quaternion::Concatenate(rot, inc);
        getActor()->setRotation(rot);
    }
    if(!Math::NearZero(mForwardSpeed)) {
        Vector3 pos = getActor()->getPosition();
        pos += getActor()->getForward() * mForwardSpeed * deltaTime;
        getActor()->setPosition(pos);
    }
}
