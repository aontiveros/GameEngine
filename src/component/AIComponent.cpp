//
// Created by tony on 2/17/20.
//

#include <SDL_log.h>
#include "../../include/component/AIComponent.h"
#include "../../include/state/AIState.h"

AIComponent::AIComponent(Actor* actor) : Component(actor) {
}

void AIComponent::registerState(AIState* state) {
    mStateMap.emplace(state->getName(), state);
}

void AIComponent::update(float deltaTime) {
    if(mState) {
        mState->update(deltaTime);
    }
}

void AIComponent::changeState(const std::string &name) {
    //Exit the old state
    if(mState) {
        mState->onExit();
    }
    auto itr = mStateMap.find(name);
    if(itr != mStateMap.end()) {
        mState = itr->second;
        //Enter the new state
        mState->onEnter();
    } else {
        SDL_Log("Could not find the state: %s in the state map!", name.c_str());
        //ensure that the state is null
        mState = nullptr;
    }
}
