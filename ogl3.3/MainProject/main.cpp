#include "Common/window_backend.h"
#include "AppTest.h"
#include "SimpleTriangle.h"
#include "ShaderTriangle.h"

int main(int argc, char** argv) {
    if(!GLFWBackendCreateWindow("TestDemo", 800, 600)) {
        return 1;
    }
    //AppTest* app = new AppTest();
    //AppTriangle* app = new AppTriangle();
    //AppIndexTriangle *app = new AppIndexTriangle();
    //ShaderTriangle *app = new ShaderTriangle();
    //UniformTriangle *app = new UniformTriangle();
    Uniform2Triangle *app = new Uniform2Triangle();
    if(!app->Init()) {
        system("pause");
        return 1;
    }
    GLFWBackendRun(app);
    delete app;
    GLFWBackenShutDown();
    system("pause");
    return 0;
}