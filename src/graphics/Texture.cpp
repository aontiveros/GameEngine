//
// Created by tony on 5/3/20.
//

#include "graphics/Texture.h"
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL_log.h>

Texture::Texture() : mTextureID(0), mHeight(0), mWidth(0) {

}

Texture::~Texture() {
    unload();
}

bool Texture::load(const std::string &fileName) {
    int channels = 0;
    unsigned char* image = SOIL_load_image(
            fileName.c_str(),
            &mWidth,
            &mHeight,
            &channels,
            SOIL_LOAD_AUTO
            );
    if(image == nullptr) {
        SDL_Log("Failed to load texture %s : %s", fileName.c_str(), SOIL_last_result());
        return false;
    }
    int format = GL_RGB;
    if (channels == 4) {
        format = GL_RGBA;
    }
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(
            GL_TEXTURE_2D,   //Texture detail
            0,     // Level of detail (for now, assume 0)
            format,      // Color format OpenGL Should use
            mWidth,      // Width of the texture
            mHeight,     // height of the texture
            0,     // Border -- "This value must be 0"
            format,      // Color format of input data
            GL_UNSIGNED_BYTE,  // Bit depth of input data; unsigned byte specified 8-bit channels
            image              // Pointer to image data
            );
    SOIL_free_image_data(image);
    // Enable bilinear texture filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return true;
}

void Texture::unload() {
    glDeleteTextures(1, &mTextureID);
}

void Texture::setActive() {
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}