//
// Created by tony on 1/1/20.
//

#ifndef CHAPTER2_ACTOR_H
#define CHAPTER2_ACTOR_H

#include <vector>
#include "../Math.h"

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
    Vector3 getPosition() { return mPosition; }
    Game* getGame() { return mGame; }

    Vector3 getForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

    void setScale(float scale);
    void setRotation(Quaternion rotation);
    float getScale() { return mScale; }
    const Quaternion& getRotation() const { return mRotation; }
    void setPosition(Vector3 position);

    //Add/Remove Components
    void addComponent(Component* component);
    void removeComponent(Component* component);

    //World Transform
    void computeWorldTransform();
    const Matrix4& getWorldTransform() const { return mWorldTransform; }

private:
    //Actors current state
    State mState;
    //Transform
    Vector3 mPosition; //The current position of the actor
    Quaternion mRotation;
    float mScale; // Uniforms the scale of the actor (1.0f for 100%)
    //list of components
    std::vector<Component*> mComponents;
    Game* mGame;
    //World transform
    Matrix4 mWorldTransform;
    bool mRecomputeWorldTransform;
};


#endif //CHAPTER2_ACTOR_H
