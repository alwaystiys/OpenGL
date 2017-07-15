#ifndef CAMERA_TEST_H
#define CAMERA_TEST_H

#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/shader_basic.h"
#include "Common/lib_math.h"
#include "Common/lib_camera.h"

namespace CameraTest {

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

class FPSTest : public ICallbacks {

public:
    FPSTest();
    ~FPSTest();
    virtual bool Init();
    virtual void RenderSceneCB();
    virtual void ProcessInput(KEY_PRESS, float);
    virtual void PorcessMouseInput(float, double, double);
    virtual void PorcessScrollInput(float, double, double);
private:
    vec3 cubePositions[10];
    vec3 cameraPos;
    vec3 cameraFront;
    vec3 cameraUp;
    GLuint VBO, VAO;
    Texture *texture1, *texture2;
    TextureShader* triangleShader;
    bool firstMouse;
    float yaw;
    float pitch;
    float lastX;
    float lastY;
    float fov;
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
    vec3 cubePositions[10];
    Camera camera;
    GLuint VBO, VAO;
    Texture *texture1, *texture2;
    TextureShader* triangleShader;

};

}


#endif CAMERA_TEST_H