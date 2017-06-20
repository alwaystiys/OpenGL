#include "Common/window_backend.h"
#include "AppTest.h"


int main(int argc, char** argv) {
    if(!GLFWBackendCreateWindow("TestDemo", 800, 600)) {
        return 1;
    }
    AppTest* app = new AppTest();
    if(!app->Init()) {
        return 1;
    }
    GLFWBackendRun(app);
    GLFWBackenShutDown();
    delete app;
    system("pause");
    return 0;
}