//
// Created by tony on 1/14/20.
//

#include "../../header/actor/Asteroid.h"
#include "../../header/Math.h"
#include "../../header/Game.h"
#include "../../header/Random.h"
#include "../../header/component/SpriteComponent.h"
#include "../../header/component/MoveComponent.h"
#include "../../header/component/CircleComponent.h"

Asteroid::Asteroid(Game *game) : Actor(game) {
    Vector3 randPos = Random::getVector(Vector3(-512.0f, -384.0f, 0.0f),
                                        Vector3(512.0f, 384.0f, 0.0f));
    setPosition(randPos);
    Quaternion q(Vector3::UnitY, -Math::PiOver2);
    q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
    setRotation(q);

    auto* sc = new SpriteComponent(this);
    sc->setTexture(game->loadTexture("Assets/Asteroid.png"));

    mc = new MoveComponent(this);
    mc->setForwardSpeed(75.0f);
    addComponent(mc);

    cc = new CircleComponent(this);
    cc->setRadius(4);

    game->addSprite(sc);
    game->addActor(this);
    addComponent(sc);
    addComponent(cc);
}

const CircleComponent& Asteroid::getCircle() const {
    return *cc;
}

void Asteroid::updateActor(float deltaTime) {
    Actor::updateActor(deltaTime);
}

void Asteroid::reflect(int x, int y) {
    mc->setForwardSpeed(-mc->getForwardSpeed());
}
