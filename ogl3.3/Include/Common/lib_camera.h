#ifndef LIB_CAMERA_H
#define LIB_CAMERA_H

#include "Common/lib_math.h"
#include "GL/glew.h"
#include <vector>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW        = -90.0f;
const float PITCH      =  0.0f;
const float SPEED      =  2.5f;
const float SENSITIVTY =  0.1f;
const float ZOOM       =  45.0f;

class Camera {
public:

    // Constructor with vectors
    Camera(
        vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // Constructor with scalar values
    Camera(
        float posX,
        float posY,
        float posZ,
        float upX,
        float upY,
        float upZ,
        float yaw,
        float pitch);

    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    mat4 GetViewMatrix();
    void processKeyboard(CameraMovement dir, float delta);
    void processMouseMovement(float delta, float xpos, float ypos, GLboolean constrainPitch = true);
    void processMouseScroll(float delta, double xoffset, double yoffset);
    // Camera Attr
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;
    // Eular Angle
    float yaw;
    float pitch;
    // Camera Options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

private:
    void updateCameraVectors();
    float lastX;
    float lastY;
    bool firstMouse;
};



#endif LIB_CAMERA_H