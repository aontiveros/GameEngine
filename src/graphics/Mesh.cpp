//
// Created by tony on 5/10/20.
//

#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <iostream>
#include "../../header/graphics/Mesh.h"
#include "../../header/Game.h"
#include "../../header/graphics/Texture.h"
#include "../../header/graphics/VertexArray.h"

Mesh::Mesh() {

}

Mesh::~Mesh() {
    delete mVertexArray;
}
// filename is the name of the mesh
bool Mesh::load(const std::string &fileName, Game *game) {
  std::ifstream ifs(fileName);
  rapidjson::IStreamWrapper isw(ifs);
  rapidjson::Document doc;
  doc.ParseStream(isw);
  if(doc.HasParseError() && !doc.IsObject() && !doc.HasMember(SPECULAR_POWER.c_str())) {
      SDL_Log("Unable to parse mesh: %s, file is not of the correct format", fileName.c_str());
      return false;
  }
  if(!parseTextureData(doc, fileName, game) || !parseVertexData(doc, fileName, game)) {
      return false;
  }
  auto vItr = doc.FindMember(SPECULAR_POWER.c_str());
  if(vItr == doc.MemberEnd() || !vItr->value.IsFloat()) {
      SDL_Log("Unable to parse mesh: %s, %s json attr must be of float type", fileName.c_str(), SPECULAR_POWER.c_str());
      return false;
  }
  mSpecularPower = vItr->value.GetFloat();
  return true;
}

Texture *Mesh::getTexture(size_t index) {
    return mTextures.at(index);
}

void Mesh::unload() {
    // Textures are owned by the game for now.
}

bool Mesh::parseTextureData(const rapidjson::Document &doc, const std::string& fileName, Game* game) {
    if(!doc.HasMember(TEXTURE_ATTRIBUTE.c_str()) ) {
        SDL_Log("Unable to find attribute: %s - please ensure %s is of correct format", TEXTURE_ATTRIBUTE.c_str(), fileName.c_str());
        return false;
    }
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(TEXTURE_ATTRIBUTE.c_str());
    if(!itr->value.IsArray()) {
        SDL_Log("Unable to parse mesh: %s, 'textures' json attr must be of array type", fileName.c_str());
        return false;
    }
    for (rapidjson::Value::ConstValueIterator tItr = itr->value.Begin(); tItr != itr->value.End(); ++tItr) {
        if(!tItr->IsString()) {
            SDL_Log("Unable to parse mesh: %s, 'textures' json attr value must be of type string", fileName.c_str());
            return false;
        }
        Texture* text = game->loadTexture(tItr->GetString());
        mTextures.emplace_back(text);
    }
    return true;
}

bool Mesh::parseVertexData(const rapidjson::Document &doc, const std::string &fileName, Game *game) {
    unsigned int* indicies;
    unsigned int indexSize = 3;
    unsigned int numOfIndicies = 0;
    float* vertices;
    unsigned int vertexSize = 8;
    unsigned int numOfVertex = 0;
    {
        if (!doc.HasMember(VERTICIES_ATTRIBUTE.c_str())) {
            SDL_Log("Unable to find attribute: %s - please ensure %s is of correct format", VERTICIES_ATTRIBUTE.c_str(),
                    fileName.c_str());
            return false;
        }
        rapidjson::Value::ConstMemberIterator itr = doc.FindMember(VERTICIES_ATTRIBUTE.c_str());
        if (!itr->value.IsArray() || itr == doc.MemberEnd()) {
            SDL_Log("The attribute %s in %s must be an array", VERTICIES_ATTRIBUTE.c_str(), fileName.c_str());
            return false;
        }
        numOfVertex = vertexSize * itr->value.Size();
        vertices = new float[numOfVertex];
        int idx = 0;
        for (auto& vItr : itr->value.GetArray()) {
            if (!vItr.IsArray()) {
                SDL_Log("Expected a array of floats, but got: %s", vItr.GetString());
                return false;
            }
            for (auto& fItr : vItr.GetArray()) {
                if (!fItr.IsNumber()) {
                    SDL_Log("Expected a array of floats, but got: %u", fItr.GetType());
                    return false;
                }
                vertices[idx++] = fItr.GetFloat();
            }
        }
    }

    {
        if (!doc.HasMember(INDICIES_ATTRIBUTE.c_str())) {
            SDL_Log("Unable to find attribute: %s - please ensure %s is of correct format", INDICIES_ATTRIBUTE.c_str(),
                    fileName.c_str());
            return false;
        }
        rapidjson::Value::ConstMemberIterator itr = doc.FindMember(INDICIES_ATTRIBUTE.c_str());
        if (!itr->value.IsArray()) {
            SDL_Log("The attribute %s in %s must be an array", INDICIES_ATTRIBUTE.c_str(), fileName.c_str());
            return false;
        }
        numOfIndicies = itr->value.Size() * indexSize;
        indicies = new unsigned int[numOfIndicies];
        int idx = 0;
        for (rapidjson::Value::ConstValueIterator vItr = itr->value.Begin(); vItr != itr->value.End(); vItr++) {
            if (!vItr->IsArray()) {
                SDL_Log("Expected a array of floats, but got: %u", vItr->GetType());
                return false;
            }
            for (rapidjson::Value::ConstValueIterator fItr = vItr->Begin(); fItr != vItr->End(); fItr++) {
                if (!fItr->IsUint()) {
                    SDL_Log("Expected a array of uints, but got: %u", fItr->GetType());
                    return false;
                }
                indicies[idx++] = fItr->GetUint();
            }
        }
    }
    mVertexArray = new VertexArray(vertices, numOfVertex, indicies, numOfIndicies);
    return true;
}
