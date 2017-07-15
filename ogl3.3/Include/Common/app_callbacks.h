#ifndef APP_CALLBACKS_H
#define APP_CALLBACKS_H


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



#endif APP_CALLBACKS_H