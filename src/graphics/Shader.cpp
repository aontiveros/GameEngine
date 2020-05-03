//
// Created by tony on 4/26/20.
//

#include <SDL_log.h>
#include <fstream>
#include <sstream>
#include "../../header/graphics/Shader.h"

Shader::Shader() {}

Shader::~Shader() {
}

bool Shader::compileShader(const std::string &fileName, GLenum shaderType, GLuint &outShader) {
    //Open the shader program file
    std::ifstream shaderFile(fileName);
    if(shaderFile.is_open()) {
        // Read all the text into a string
        std::stringstream ss;
        ss << shaderFile.rdbuf();
        std::string contents(ss.str());
        const char* contentsChar = contents.c_str();

        //Create a shader of the specified type
        outShader = glCreateShader(shaderType);
        //Set the source characters and attempt to compile
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);

        if(isCompiled(outShader)) {

        } else {
            SDL_Log("Failed to compile shader from file: %s", fileName.c_str());
            return false;
        }
    } else {
        SDL_Log("Shader file not found: %s", fileName.c_str());
        return false;
    }
    return true;
}

bool Shader::isCompiled(GLuint shader) {
    GLint status;
    // Query the shader compilation status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compilation failed:\n%s", buffer);
        return false;
    }
    return true;
}

bool Shader::load(const std::string &vertName, const std::string &fragName) {
    if(!compileShader(vertName, GL_VERTEX_SHADER, mVertexShader) ||
    !compileShader(fragName, GL_FRAGMENT_SHADER, mFragShader)) {
        return false;
    }

    // Now create a shader program that links the vertex/frag shader together
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragShader);
    glLinkProgram(mShaderProgram);

    // verify that the program linked success
    return isValidProgram();
}

bool Shader::isValidProgram() {
    GLint status;
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
        SDL_Log("GLSL Compilation failed:\n%s", buffer);
        return false;
    }
    return true;
}

void Shader::setActive() {
    glUseProgram(mShaderProgram);
}

void Shader::unload() {
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}