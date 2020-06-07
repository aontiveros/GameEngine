//
// Created by tony on 1/1/20.
//

#ifndef CHAPTER2_COMPONENT_H
#define CHAPTER2_COMPONENT_H

#include <cstdint>

//forward declarations
class Actor;

class Component {
public:
    // Constructor
    // The lower the update the order, the later the component updates
    Component(Actor* actor, int updateOrder = 100);
    //Destructor
    virtual ~Component();
    //update this component using dela time
    virtual void update(float deltaTime);
    //Callback when world transform is updated
    virtual void onUpdateWorldTransform() {}

    virtual void processInput(const uint8_t *keyState);

    //getter
    Actor* getActor() { return mActor; }
    int getUpdateOrder() { return mUpdateOrder; }

private:
    //Owning actor
    Actor* mActor;
    //the set update order
    int mUpdateOrder;

};


#endif //CHAPTER2_COMPONENT_H
