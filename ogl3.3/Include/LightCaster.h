#ifndef LIGHT_CASTER_H
#define LIGHT_CASTER_H

#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/shader_basic.h"
#include "Common/lib_math.h"
#include "Common/lib_camera.h"


namespace LightCasterTest {

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

/************************************************************************/
/*	平行光示例
/************************************************************************/
class LightCaster : public ICallbacks {

public:
    LightCaster();
    ~LightCaster();
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
    Texture *diffuseMap, *specularMap, *emissionMap;
    vec3 cubePositions[10];
};


/************************************************************************/
/*	点光源示例
/************************************************************************/
class PointLightsTest : public ICallbacks {

public:
    PointLightsTest();
    ~PointLightsTest();
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
    Texture *diffuseMap, *specularMap, *emissionMap;
    vec3 cubePositions[10];
};


/************************************************************************/
/*	聚光示例
/************************************************************************/
class SpotlightTest : public ICallbacks {

public:
    SpotlightTest();
    ~SpotlightTest();
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
    Texture *diffuseMap, *specularMap, *emissionMap;
    vec3 cubePositions[10];
};


/************************************************************************/
/*	聚光示例
/************************************************************************/
class BetterSpotlightTest : public ICallbacks {

public:
    BetterSpotlightTest();
    ~BetterSpotlightTest();
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
    Texture *diffuseMap, *specularMap, *emissionMap;
    vec3 cubePositions[10];
};

}



#endif LIGHT_CASTER_H