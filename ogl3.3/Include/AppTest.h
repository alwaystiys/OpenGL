
#ifndef APP_TEST_H
#define APP_TEST_H

#include "Common/app_callbacks.h"
#include <iostream>

class AppTest : public ICallbacks {

public:

    AppTest();
    virtual bool Init();
    virtual void RenderSceneCB();


};

#endif APP_TEST_H