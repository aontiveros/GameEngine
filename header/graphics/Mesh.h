//
// Created by tony on 5/10/20.
//

#ifndef CHAPTER2_MESH_H
#define CHAPTER2_MESH_H


#include <string>
#include <vector>

//forward declaration
class Game;
class VertexArray;
class Texture;

class Mesh {
public:
    Mesh();
    ~Mesh();
    //Load and unload the mesh
    bool load(const std::string& fileName, Game* game);
    void unload();
    // Get the vertex array associated with this mesh
    VertexArray* getVertexArray() { return mVertexArray; }
    // Get the texture from the specified index
    Texture* getTexture(size_t index);
    // Get the name of the shader
    const std::string& getShaderName() const { return mShaderName; }
    //Get the object space bounding the sphere radius
    float getRadius() const { return mRadius; }
private:
    // Vertex Array associated with this mesh
    VertexArray* mVertexArray;
    // Textures associated with this mesh
    std::vector<Texture*> mTextures;
    // Name of the shader associated with this mesh
    std::string mShaderName;
    // Stores the object space bounding sphere radius
    float mRadius;

    const std::string TEXTURE_ATTRIBUTE = "textures";
};


#endif //CHAPTER2_MESH_H
