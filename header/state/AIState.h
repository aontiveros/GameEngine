//
// Created by tony on 3/7/20.
//

#ifndef CHAPTER2_AISTATE_H
#define CHAPTER2_AISTATE_H

class AIComponent;

class AIState {
public:
    AIState(AIComponent* owner) : mOwner(owner) {}

    virtual void update(float deltaTime) = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    //Getter for the string name of the state
    virtual const char* getName() = 0;
protected:
    AIComponent* mOwner;
};


#endif //CHAPTER2_AISTATE_H
