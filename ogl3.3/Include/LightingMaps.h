#ifndef LIGHTING_MAPS_H
#define LIGHTING_MAPS_H

#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/shader_basic.h"
#include "Common/lib_math.h"
#include "Common/lib_camera.h"


namespace LightMapsTest {

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
    Texture *diffuseMap, *specularMap;
};
}



#endif LIGHTING_MAPS_H