//
// Created by tony on 5/3/20.
//

#ifndef CHAPTER2_TEXTURE_H
#define CHAPTER2_TEXTURE_H


#include <string>

class Texture {
public:
Texture();
~Texture();

bool load(const std::string& fileName);
void unload();

void setActive();

int getWidth() const { return mWidth; }
int getHeight() const { return mHeight; }
private:
    //OpenGL id of the texture
    unsigned int mTextureID;
    // Width / height of the texture
    int mWidth;
    int mHeight;
};


#endif //CHAPTER2_TEXTURE_H
