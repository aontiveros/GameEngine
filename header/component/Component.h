//
// Created by tony on 1/1/20.
//

#ifndef CHAPTER2_COMPONENT_H
#define CHAPTER2_COMPONENT_H

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
