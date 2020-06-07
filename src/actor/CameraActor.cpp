//
// Created by tony on 5/25/20.
//

#include "actor/Actor.h"
#include "actor/CameraActor.h"
#include "Game.h"
#include "component/MoveComponent.h"
#include "graphics/Renderer.h"

CameraActor::CameraActor(struct Game *game) : Actor(game) {
    mMoveComp = new MoveComponent(this);
}

void CameraActor::updateActor(float deltaTime) {
    Actor::updateActor(deltaTime);

    // Compute new camera from this actor
    Vector3 cameraPos = getPosition();
    Vector3 target = getPosition() + getForward() * 100.0f;
    Vector3 up = Vector3::UnitZ;

    Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
    getGame()->getRenderer()->setViewMatrix(view);
}

void CameraActor::actorInput(const uint8_t *keyState) {
    if (getState() == EActive) {
        float fowardSpeed = 0.0f;
        float angularSpeed = 0.0f;
        if (keyState[SDL_SCANCODE_W]) {
            fowardSpeed += 300.0f;
        }
        if (keyState[SDL_SCANCODE_S]) {
            fowardSpeed -= 300.0f;
        }
        if (keyState[SDL_SCANCODE_A]) {
            angularSpeed -= Math::Pi;
        }
        if (keyState[SDL_SCANCODE_D]) {
            angularSpeed += Math::Pi;
        }
        mMoveComp->setForwardSpeed(fowardSpeed);
        mMoveComp->setAngularSpeed(angularSpeed);
    }
}