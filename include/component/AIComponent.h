//
// Created by tony on 2/17/20.
//

#ifndef CHAPTER2_AICOMPONENT_H
#define CHAPTER2_AICOMPONENT_H

#include <string>
#include <unordered_map>
#include "Component.h"

//forward declarations
class Actor;
class AIState;

class AIComponent : public Component {

public:
    AIComponent(Actor* actor);
    void update(float deltaTime) override;
    void changeState(const std::string& name);


    //Add a new state to the map
    void registerState(AIState* state);


private:
    //Maps name of state to AIState instance
    std::unordered_map<std::string, AIState*> mStateMap;

    //Current state that we are in
    AIState* mState;

};


#endif //CHAPTER2_AICOMPONENT_H
