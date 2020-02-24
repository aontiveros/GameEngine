//
// Created by tony on 1/27/20.
//

#include "../../header/component/CircleComponent.h"
#include "../../header/Actor.h"

CircleComponent::CircleComponent(Actor *actor) : Component(actor) {
}

const bool intersect(const CircleComponent& first, const CircleComponent& second) {
    const Vector2& intersect = first.getCenter() - second.getCenter();
    float distSq = intersect.LengthSq();

    float radii = first.getRadius() - second.getRadius();
    radii *= radii;
    return distSq <= radii;
}
