#include "Common/app_callbacks.h"
#include <GLFW/glfw3.h>
#include "Common/lib_math.h"

CommonCallbacks::CommonCallbacks():camera(vec3(0.0f, 0.0f, 5.0f)){

}

CommonCallbacks::~CommonCallbacks() {

}

void CommonCallbacks::ProcessInput(KEY_PRESS isKeyPress, float delta) {
    if(isKeyPress(GLFW_KEY_W)) {
        camera.processKeyboard(FORWARD, delta);
    }
    if(isKeyPress(GLFW_KEY_S)) {
        camera.processKeyboard(BACKWARD, delta);
    }
    if(isKeyPress(GLFW_KEY_A)) {
        camera.processKeyboard(LEFT, delta);
    }
    if(isKeyPress(GLFW_KEY_D)) {
        camera.processKeyboard(RIGHT, delta);
    }
}

void CommonCallbacks::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void CommonCallbacks::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}