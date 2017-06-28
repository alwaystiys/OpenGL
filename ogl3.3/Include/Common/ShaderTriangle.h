
#ifndef SHADER_TRIANGLE_H
#define SHADER_TRIANGLE_H

#include "Common/app_callbacks.h"
#include "Common/shader_basic.h"
#include <iostream>




class InnterShader : public ShaderBasic {
public:
    InnterShader();
    virtual bool Init();

};

class ShaderTriangle : public ICallbacks {

public:
    ShaderTriangle();
    ~ShaderTriangle();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO, EBO;
    InnterShader* innterShader;
};

#endif SHADER_TRIANGLE_H