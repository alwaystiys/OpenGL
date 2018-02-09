#ifndef APP_CALLBACKS_H
#define APP_CALLBACKS_H

#include "Common/lib_camera.h"

typedef bool (*KEY_PRESS)(int);

class ICallbacks {
public:
    virtual bool Init() {
        return true;
    };
    virtual void GLClearConfig() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    };
    virtual void PreRenderConfig() {
        glEnable(GL_DEPTH_TEST);
    };
    virtual void RenderSceneCB() {};
    virtual void ProcessInput(KEY_PRESS, float) {};
    virtual void PorcessMouseInput(float, double, double) {};
    virtual void PorcessScrollInput(float, double, double) {};

};

class CommonCallbacks : public ICallbacks {
public:
    CommonCallbacks();
    ~CommonCallbacks();
    virtual bool Init() {
        return true;
    };
    virtual void PreRenderConfig() {};
    virtual void RenderSceneCB() {};
    virtual void ProcessInput(KEY_PRESS, float);
    virtual void PorcessMouseInput(float, double, double);
    virtual void PorcessScrollInput(float, double, double);
protected:
    Camera camera;
};

#endif APP_CALLBACKS_H