#ifndef TEXTURE_TEST_H
#define TEXTURE_TEST_H

#include "Common/app_callbacks.h"
#include "Common/shader_basic.h"
#include <iostream>


class TextureShader : public ShaderBasic {
public:
    TextureShader(const char *vertexShaderSource, const char *fragmentShaderSource);
    virtual bool Init();
private:
    const char *vertexShaderSource;
    const char *fragmentShaderSource;

};

class SimpleTexture : public ICallbacks {

public:
    SimpleTexture();
    ~SimpleTexture();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO, EBO;
    TextureShader* triangleShader;
};




#endif TEXTURE_TEST_H