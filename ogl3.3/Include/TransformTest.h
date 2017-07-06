#ifndef TRANSFORM_TEST_H
#define TRANSFORM_TEST_H

#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/shader_basic.h"

namespace TransformTest {

class TextureShader : public ShaderBasic {
public:
    TextureShader(const char *vertexShaderSource, const char *fragmentShaderSource, const char *vsFilePath, const char *fsFilePath);
    virtual bool Init();
private:
    const char *vertexShaderSource;
    const char *fragmentShaderSource;
    const char *vsFilePath;
    const char *fsFilePath;
};

class MultipleTexture : public ICallbacks {

public:
    MultipleTexture();
    ~MultipleTexture();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO, EBO;
    Texture *texture1, *texture2;
    TextureShader* triangleShader;
};

}






#endif TRANSFORM_TEST_H
