
#ifndef APP_TRIANGLE_H
#define APP_TRIANGLE_H

#include "Common/app_callbacks.h"
#include "Common/shader_basic.h"
#include <iostream>


class InnterShader : public ShaderBasic {
public:
    InnterShader(const char *vertexShaderSource, const char *fragmentShaderSource);
    virtual bool Init();
private:
    const char *vertexShaderSource;
    const char *fragmentShaderSource;

};

class ShaderTriangle : public ICallbacks {

public:
    ShaderTriangle();
    ~ShaderTriangle();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO;
    InnterShader* triangleShader;
};

//*************************************************


class UniformTriangle : public ICallbacks {

public:
    UniformTriangle();
    ~UniformTriangle();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO;
    InnterShader* triangleShader;
};

//*************************************************

class Uniform2Triangle : public ICallbacks {

public:
    Uniform2Triangle();
    ~Uniform2Triangle();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO;
    InnterShader* triangleShader;
};







#endif APP_TRIANGLE_H