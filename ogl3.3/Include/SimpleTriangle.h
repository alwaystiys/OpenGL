
#ifndef SIMPLE_TRIANGLE_H
#define SIMPLE_TRIANGLE_H

#include "Common/app_callbacks.h"
#include "Common/shader_basic.h"
#include <iostream>


class TriangleShader : public ShaderBasic {
public:
    TriangleShader();
    virtual bool Init();

};




class AppTriangle : public ICallbacks {
public:
    AppTriangle();
    ~AppTriangle();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO;
    TriangleShader* triangleShader;
};


class AppIndexTriangle : public ICallbacks {

public:
    AppIndexTriangle();
    ~AppIndexTriangle();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO, EBO;
    TriangleShader* triangleShader;
};

#endif SIMPLE_TRIANGLE_H