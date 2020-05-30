//
// Created by tony on 5/18/20.
//

#include "component/MeshComponent.h"
#include "graphics/Shader.h"
#include "actor/Actor.h"
#include "graphics/Mesh.h"
#include "graphics/VertexArray.h"
#include "graphics/Texture.h"
#include "Game.h"
#include "graphics/Renderer.h"

MeshComponent::MeshComponent(Actor *actor) : Component(actor), mMesh(nullptr), mTextureIndex(0) {
    getActor()->getGame()->getRenderer()->addMeshComponent(this);
}

MeshComponent::~MeshComponent() {
    getActor()->getGame()->getRenderer()->removeMeshComponent(this);
}

void MeshComponent::draw(Shader *shader) {
    if (mMesh != nullptr) {
        // set the world transform
        shader->setMatrixUniform("uWorldTransform",
                getActor()->getWorldTransform());
        // Set the specular power
        shader->setFloatUniform("uSpecPower", mMesh->getSpecularPower());
        //set the active texture
        Texture* t = mMesh->getTexture(mTextureIndex);
        if( t != nullptr) {
            t->setActive();
        }
        // Set the mesh's vertex array as active
        VertexArray* va = mMesh->getVertexArray();
        va->setActive();
        // Draw
        glDrawElements(
                GL_TRIANGLES,
                va->getNumIndices(),
                GL_UNSIGNED_INT,
                nullptr
                );
    }
}

void MeshComponent::setMesh(Mesh *mesh) {
    this->mMesh = mesh;
}

void MeshComponent::setTextureIndex(size_t index) {
     mTextureIndex = index;
}
