#ifndef APP_CALLBACKS_H
#define APP_CALLBACKS_H

#include "Common/lib_camera.h"

typedef bool (*KEY_PRESS)(int);

class ICallbacks {
public:
    virtual bool Init() {
        return true;
    };
    virtual void RenderSceneCB() {};
    virtual void ProcessInput(KEY_PRESS, float) {};
    virtual void PorcessMouseInput(float, double, double) {};
    virtual void PorcessScrollInput(float, double, double) {};

};

class CommonCallbacks : public ICallbacks{
public:
	 CommonCallbacks();
    ~CommonCallbacks();
	virtual bool Init() {
		return true;
	};
	virtual void RenderSceneCB() {};
	virtual void ProcessInput(KEY_PRESS, float);
	virtual void PorcessMouseInput(float, double, double);
	virtual void PorcessScrollInput(float, double, double);
protected:
	Camera camera;
};

#endif APP_CALLBACKS_H