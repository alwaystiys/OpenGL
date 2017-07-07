#include "Common/lib_transform.h"

Transform::Transform() {
}

Transform::~Transform() {
}

Transform& Transform::translate(float x, float y, float z) {
    transform = glm::translate(transform, glm::vec3(x, y, z));
    return *this;
}

Transform& Transform::rotate(float angle, float x, float y, float z) {
    transform = glm::rotate(transform, angle, glm::vec3(x, y, z));
    return *this;
}

Transform& Transform::scale() {
    //return this->transform;
    return *this;
}

float* Transform::getTransformResult() {
    return glm::value_ptr(transform);
}