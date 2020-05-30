//
// Created by tony on 5/25/20.
//

#ifndef CHAPTER2_CAMERAACTOR_H
#define CHAPTER2_CAMERAACTOR_H

#include "Actor.h"

class CameraActor : public Actor
{
public:
    CameraActor(class Game* game);

    void updateActor(float deltaTime) override;
 //   void actprInput(const uint8_t* keys) override;
private:
    class MoveComponent* mMoveComp;
};

#endif //CHAPTER2_CAMERAACTOR_H
