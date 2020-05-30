//
// Created by tony on 1/14/20.
//

#ifndef CHAPTER2_MOVECOMPONENT_H
#define CHAPTER2_MOVECOMPONENT_H

#include "Component.h"

class Actor;

class MoveComponent : public Component {
public:
    MoveComponent(Actor* actor, int updateOwner = 10);

    void update(float deltaTime) override;

    float getAngularSpeed() const { return mAngularSpeed; }
    float getForwardSpeed() const { return mForwardSpeed; }
    void setAngularSpeed(float angularSpeed) { mAngularSpeed = angularSpeed; }
    void setForwardSpeed(float forwardSpeed) { mForwardSpeed = forwardSpeed; }

private:
    float mAngularSpeed;
    float mForwardSpeed;
};


#endif //CHAPTER2_MOVECOMPONENT_H
