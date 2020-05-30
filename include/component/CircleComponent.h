//
// Created by tony on 1/27/20.
//

#ifndef CHAPTER2_CIRCLECOMPONENT_H
#define CHAPTER2_CIRCLECOMPONENT_H

#include "Component.h"
#include "Math.h"

class Actor;
class Vector2;

class CircleComponent : public Component {
public:
    CircleComponent(Actor* actor);

    void setRadius(float radius) { mRadius = radius; }
    float getRadius() const { return mRadius; }

    const Vector2 & getCenter() const { return mCenter; };

private:
    Vector2 mCenter;
    float mRadius;
};

const bool intersect (const CircleComponent& first, const CircleComponent& second);

#endif //CHAPTER2_CIRCLECOMPONENT_H
