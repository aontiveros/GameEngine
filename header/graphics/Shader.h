//
// Created by tony on 4/26/20.
//

#ifndef CHAPTER2_SHADER_H
#define CHAPTER2_SHADER_H


#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader();
    ~Shader();

    //Load the vertex/fragment shaders for the given name
    bool load(const std::string& vertName, const std::string& fragName);
    void unload();
    // This is the active shader program
    void setActive();

private:
    // Tries to compile the specified shader
    bool compileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
    // Tests whether shader has compiled successfully
    bool isCompiled(GLuint shader);
    // Tests whether vertex/fragment programs link
    bool isValidProgram();
    // Store the shader object IDs
    GLuint mVertexShader;
    GLuint mFragShader;
    GLuint mShaderProgram;
};


#endif //CHAPTER2_SHADER_H
