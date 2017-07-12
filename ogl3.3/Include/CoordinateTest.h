#ifndef COORDINATE_TEST_H
#define COORDINATE_TEST_H


#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/shader_basic.h"
#include "Common/lib_math.h"

namespace CoordinateTest {

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

class CubeIndiceTest : public ICallbacks {

public:
    CubeIndiceTest();
    ~CubeIndiceTest();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO, EBO;
    Texture *texture1, *texture2;
    TextureShader* triangleShader;
};

class CubeTest : public ICallbacks {

public:
    CubeTest();
    ~CubeTest();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, VAO;
    Texture *texture1, *texture2;
    TextureShader* triangleShader;
};

class MutitudeCubeTest : public ICallbacks {

public:
    MutitudeCubeTest();
    ~MutitudeCubeTest();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    vec3 cubePositions[10];
    GLuint VBO, VAO;
    Texture *texture1, *texture2;
    TextureShader* triangleShader;
};

}


#endif COORDINATE_TEST_H