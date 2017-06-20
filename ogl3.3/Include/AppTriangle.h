
#ifndef APP_TRIANGLE_H
#define APP_TRIANGLE_H

#include "Common/app_callbacks.h"
#include <iostream>

class AppTriangle : public ICallbacks {

    AppTriangle();
    virtual bool Init();
    virtual void RenderSceneCB();
};


#endif APP_TRIANGLE_H