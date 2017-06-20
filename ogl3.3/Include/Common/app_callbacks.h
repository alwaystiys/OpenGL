#ifndef APP_CALLBACKS_H
#define APP_CALLBACKS_H

class ICallbacks {
public:
    virtual bool Init() {
        return true;
    };
    virtual void RenderSceneCB() {};
};



#endif APP_CALLBACKS_H