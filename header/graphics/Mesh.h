//
// Created by tony on 5/10/20.
//

#ifndef CHAPTER2_MESH_H
#define CHAPTER2_MESH_H


#include <string>
#include <vector>
#include <rapidjson/document.h>

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
    // Get the specular power!!!
    float getSpecularPower() const { return mSpecularPower; }
private:
    // Vertex Array associated with this mesh
    VertexArray* mVertexArray;
    // Textures associated with this mesh
    std::vector<Texture*> mTextures;
    // Name of the shader associated with this mesh
    std::string mShaderName;
    // Stores the object space bounding sphere radius
    float mRadius;
    // Specular power
    float mSpecularPower;

    const std::string TEXTURE_ATTRIBUTE = "textures";
    const std::string VERTICIES_ATTRIBUTE = "vertices";
    const std::string INDICIES_ATTRIBUTE = "indices";
    const std::string SPECULAR_POWER = "specularPower";

    bool parseTextureData(const rapidjson::Document &doc, const std::string& fileName, Game* game);
    bool parseVertexData(const rapidjson::Document &doc, const std::string& fileName, Game* game);
};


#endif //CHAPTER2_MESH_H
