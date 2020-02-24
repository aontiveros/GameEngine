//
// Created by tony on 2/17/20.
//

#ifndef CHAPTER2_AICOMPONENT_H
#define CHAPTER2_AICOMPONENT_H

enum State {
    Patrol,
    Death,
    Attack
};

class AIComponent {

public:
    AIComponent();
    void update(float deltaTime);

private:

    State mState;

    void updateAttack(float deltaTime);
    void updatePatrol(float deltaTime);
    void updateDeath(float deltaTime);
};


#endif //CHAPTER2_AICOMPONENT_H
