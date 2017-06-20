#include "AppTriangle.h"

AppTriangle::AppTriangle() {
}

bool AppTriangle::Init() {
    std::cout << "Init" << std::endl;
    return true;
}

void AppTriangle::RenderSceneCB() {
    std::cout << "RenderSceneCB" << std::endl;
}
