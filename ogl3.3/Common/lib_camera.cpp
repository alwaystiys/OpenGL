#include "Common/lib_camera.h"

// Constructor with vectors
Camera::Camera(vec3 position, vec3 up, float yaw, float pitch)
    : front(vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM), firstMouse(true) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}
// Constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : front(vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVTY), zoom(ZOOM), firstMouse(true) {
    this->position = vec3(posX, posY, posZ);
    this->worldUp = vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

void Camera::processKeyboard(CameraMovement dir, float delta) {
    float velocity = movementSpeed * delta; // adjust accordingly
    if(dir == FORWARD)
        position += front * velocity;
    if(dir == BACKWARD)
        position -= front * velocity;
    if(dir == LEFT)
        position -= right * velocity;
    if(dir == RIGHT)
        position += right * velocity;
}

void Camera::processMouseMovement(float delta, float xpos, float ypos, GLboolean constrainPitch) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;
    yaw += xoffset;
    pitch += yoffset;
    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if(constrainPitch) {
        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::processMouseScroll(float delta, double xoffset, double yoffset) {
    if(zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if(zoom <= 1.0f)
        zoom = 1.0f;
    if(zoom >= 45.0f)
        zoom = 45.0f;
}

mat4 Camera::GetViewMatrix() {
    return libmath::genLookAtMatrix(position, position + front, up);
}

void Camera::updateCameraVectors() {
    vec3 tempFront;
    tempFront.x = cos(libmath::toRadians(yaw)) * cos(libmath::toRadians(pitch));
    tempFront.y = sin(libmath::toRadians(pitch));
    tempFront.z = sin(libmath::toRadians(yaw)) * cos(libmath::toRadians(pitch));
    front = libmath::normalize(tempFront);
    // Also re-calculate the Right and Up vector
    right = libmath::normalize(libmath::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = libmath::normalize(libmath::cross(right, front));
}

