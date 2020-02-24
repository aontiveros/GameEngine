//
// Created by tony on 1/1/20.
//

#ifndef CHAPTER2_ACTOR_H
#define CHAPTER2_ACTOR_H

#include <vector>
#include "Math.h"

//forward declarations
class Game;
class Component;

class Actor {
public:
    enum State {
        EActive,
        EPaused,
        EDead
    };

    Actor(Game* game);
    virtual ~Actor();

    //Update function called from within a game (not overridable)
    void update(float deltaTime);
    //Updates all components part of this actor (not overridable)
    void updateComponents(float deltaTime);
    //Any actor-specific logic to update (overridable)
    virtual void updateActor(float deltaTime);

    //Getters and Setters
    State getState() { return mState; }
    Vector2 getPosition() { return mPosition; }
    Game* getGame() { return mGame; }

    Vector2 getForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

    void setScale(float scale) { mScale = scale; }
    void setRotation(float rotation) { mRotation = rotation;}
    float getScale() { return mScale; }
    float getRotation() { return mRotation; }
    void setPosition(Vector2 position);

    //Add/Remove Components
    void addComponent(Component* component);
    void removeComponent(Component* component);

private:
    //Actors current state
    State mState;
    //Transform
    Vector2 mPosition; //The current position of the actor
    float mScale; // Uniforms the scale of the actor (1.0f for 100%)
    float mRotation; // Rotation angle (radians)
    //list of components
    std::vector<Component*> mComponents;
    Game* mGame;
};


#endif //CHAPTER2_ACTOR_H
