//
// Created by tony on 5/10/20.
//

#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <iostream>
#include "graphics/Mesh.h"
#include "Game.h"
#include "graphics/Texture.h"
#include "graphics/VertexArray.h"
#include "Math.h"

Mesh::Mesh() : mVertexArray(nullptr), mRadius(0.0f), mSpecularPower(100.0f) {

}

Mesh::~Mesh() {

}
// filename is the name of the mesh
bool Mesh::load(const std::string &fileName, Game *game) {
  mShaderName = fileName;
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
    if(index < mTextures.size() && index >= 0) {
        return mTextures.at(index);
    }
    return nullptr;
}

void Mesh::unload() {
    // Textures are owned by the game for now.
    delete mVertexArray;
    mVertexArray = nullptr;
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
    size_t indexSize = 3;
    size_t vertSize = 8;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    float radius = 0.0f;
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
        unsigned int numOfVertex = vertSize * itr->value.Size();
        vertices.reserve(numOfVertex);
        for (auto& vItr : itr->value.GetArray()) {
            if (!vItr.IsArray()) {
                SDL_Log("Expected a array of floats, but got: %s", vItr.GetString());
                return false;
            }
            Vector3 pos(vItr[0].GetFloat(), vItr[1].GetFloat(), vItr[2].GetFloat());
            radius = Math::Max(mRadius, pos.LengthSq());
            for (auto& fItr : vItr.GetArray()) {
                if (!fItr.IsNumber()) {
                    SDL_Log("Expected a array of floats, but got: %u", fItr.GetType());
                    return false;
                }
                vertices.emplace_back(static_cast<float>(fItr.GetDouble()));
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
        size_t numOfIndices = itr->value.Size() * indexSize;
        indices.reserve(numOfIndices);
        for (rapidjson::Value::ConstValueIterator vItr = itr->value.Begin(); vItr != itr->value.End(); vItr++) {
            if (!vItr->IsArray()) {
                SDL_Log("Expected a array of floats, but got: %u", vItr->GetType());
                return false;
            }
            for (rapidjson::Value::ConstValueIterator fItr = vItr->Begin(); fItr != vItr->End(); fItr++) {
                if (!fItr->IsUint(  )) {
                    SDL_Log("Expected a array of uint, but got: %u", fItr->GetType());
                    return false;
                }
                indices.emplace_back(fItr->GetUint());
            }
        }
    }
    mRadius = Math::Sqrt(radius);
    mVertexArray = new VertexArray(vertices.data(), static_cast<unsigned int>(vertices.size()) / vertSize, indices.data(),
                                   static_cast<unsigned int>(indices.size()));
    return true;
}
