#ifndef COLOR_TEST_H
#define COLOR_TEST_H

#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/shader_basic.h"
#include "Common/lib_math.h"
#include "Common/lib_camera.h"

namespace LightTest {

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

class FPS2Test : public ICallbacks {

public:
    FPS2Test();
    ~FPS2Test();
    virtual bool Init();
    virtual void RenderSceneCB();
    virtual void ProcessInput(KEY_PRESS, float);
    virtual void PorcessMouseInput(float, double, double);
    virtual void PorcessScrollInput(float, double, double);

private:
    Camera camera;
    GLuint VBO, cubeVAO, lightVAO;
    TextureShader *lightingShader, *lambShader;

};

class BasicLightTest : public ICallbacks {

public:
    BasicLightTest();
    ~BasicLightTest();
    virtual bool Init();
    virtual void RenderSceneCB();
    virtual void ProcessInput(KEY_PRESS, float);
    virtual void PorcessMouseInput(float, double, double);
    virtual void PorcessScrollInput(float, double, double);

private:
    Camera camera;
    GLuint VBO, cubeVAO, lightVAO;
    vec3 lightPos;
    TextureShader *lightingShader, *lambShader;

};

class MaterialTest : public ICallbacks {

public:
    MaterialTest();
    ~MaterialTest();
    virtual bool Init();
    virtual void RenderSceneCB();
    virtual void ProcessInput(KEY_PRESS, float);
    virtual void PorcessMouseInput(float, double, double);
    virtual void PorcessScrollInput(float, double, double);

private:
    Camera camera;
    GLuint VBO, cubeVAO, lightVAO;
    vec3 lightPos;
    TextureShader *lightingShader, *lambShader;

};
}

#endif COLOR_TEST_H