//
// Created by tony on 5/10/20.
//

#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include "../../header/graphics/Mesh.h"
#include "../../header/Game.h"
#include "../../header/graphics/Texture.h"

Mesh::Mesh() {

}

Mesh::~Mesh() {

}
// filename is the name of the mesh
bool Mesh::load(const std::string &fileName, Game *game) {
  std::ifstream ifs(fileName);
  rapidjson::IStreamWrapper isw(ifs);
  rapidjson::Document doc;
  doc.ParseStream(isw);
  if(doc.HasParseError() && !doc.IsObject() && !doc.HasMember(TEXTURE_ATTRIBUTE.c_str())) {
      SDL_Log("Unable to parse mesh: %s, file is not of the correct format", fileName.c_str());
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

Texture *Mesh::getTexture(size_t index) {
    return mTextures.at(index);
}

void Mesh::unload() {
    // Textures are owned by the game for now.

}
