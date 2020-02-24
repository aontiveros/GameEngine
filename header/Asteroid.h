//
// Created by tony on 1/14/20.
//

#ifndef CHAPTER2_ASTEROID_H
#define CHAPTER2_ASTEROID_H

#include "../header/Actor.h"

class CircleComponent;
class MoveComponent;


class Asteroid : public Actor {
public:
    Asteroid(Game* game);

    const CircleComponent& getCircle() const;

    void updateActor(float deltaTime) override;

    void reflect(int x, int y);
private:
    CircleComponent* cc;
    MoveComponent* mc;
};


#endif //CHAPTER2_ASTEROID_H
