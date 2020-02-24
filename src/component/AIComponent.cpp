//
// Created by tony on 2/17/20.
//

#include <SDL_log.h>
#include "../../header/component/AIComponent.h"

AIComponent::AIComponent() {
    mState = State::Patrol;
}


void AIComponent::update(float deltaTime) {
    switch (mState) {
        case Patrol:
            updatePatrol(deltaTime);
            break;
        case Attack:
            updateAttack(deltaTime);
            break;
        case Death:
            updateDeath(deltaTime);
            break;
        default:
            SDL_Log("Unknown state: %d", mState);
    }
}

void AIComponent::updatePatrol(float deltaTime) {
    //Do a patrol
}

void AIComponent::updateAttack(float deltaTime) {
    //Do a patrol
}

void AIComponent::updateDeath(float deltaTime) {
    
}