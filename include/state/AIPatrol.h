//
// Created by tony on 3/7/20.
//

#ifndef CHAPTER2_AIPATROL_H
#define CHAPTER2_AIPATROL_H

#include "state/AIState.h"

//forward declarations
class Component;

class AIPatrol : public AIState {
public:
    AIPatrol(AIComponent* component);

    void update(float deltaTime) override;
    void onEnter() override;
    void onExit() override;

    const char* getName() {
        return "AIState::Patrol";
    }
};


#endif //CHAPTER2_AIPATROL_H
