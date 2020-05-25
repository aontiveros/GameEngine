//
// Created by tony on 4/26/20.
//

#ifndef CHAPTER2_SHADER_H
#define CHAPTER2_SHADER_H


#include <string>
#include <GL/glew.h>

//forward declare
class Matrix4;
class Vector3;

class Shader {
public:
    Shader();
    ~Shader();

    //Load the vertex/fragment shaders for the given name
    bool load(const std::string& vertName, const std::string& fragName);
    void unload();
    // This is the active shader program
    void setActive();
    //set uniform in opengl
    void setMatrixUniform(const char* name, const Matrix4& matrix);
    // set uniform vector
    void setVectorUniform(const char* name, Vector3 vector);
    void setFloatUniform(const char* name, float fl);

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
