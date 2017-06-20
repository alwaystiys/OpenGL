#include "AppTest.h"

AppTest::AppTest() {
}

bool AppTest::Init() {
    std::cout << "Init" << std::endl;
    return true;
}

void AppTest::RenderSceneCB() {
    std::cout << "RenderSceneCB" << std::endl;
}
