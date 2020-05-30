//
// Created by tony on 5/18/20.
//

#ifndef CHAPTER2_MESHCOMPONENT_H
#define CHAPTER2_MESHCOMPONENT_H

#include <cstddef>
#include "Component.h"

//forward declarations
class Shader;
class Mesh;

class MeshComponent : public Component {
public:
    MeshComponent(Actor *actor);
    ~MeshComponent();
    // Draw this mesh component with provided shader
    virtual void draw(Shader* shader);
    // Set the mesh/texture index used by the mesh component
    virtual void setMesh(Mesh* mesh);
    void setTextureIndex(size_t index);
private:
    Mesh* mMesh;
    size_t mTextureIndex;
};


#endif //CHAPTER2_MESHCOMPONENT_H
