#include "Common/lib_transform.h"

Transform::Transform() {
}

Transform::Transform(glm::mat4 matrix) {
    transform = matrix;
}

Transform::~Transform() {
}

void Transform::reset() {
	mat4 object;
	transform = object;
}

Transform& Transform::translate(vec3 v) {
    transform = glm::translate(transform, v);
    return *this;
}

Transform& Transform::translate(float x, float y, float z) {
    transform = glm::translate(transform, glm::vec3(x, y, z));
    return *this;
}

Transform& Transform::rotate(float angle, float x, float y, float z) {
    transform = glm::rotate(transform, angle, glm::vec3(x, y, z));
    return *this;
}

Transform& Transform::scale(float x, float y, float z) {
    transform = glm::scale(transform, glm::vec3(x, y, z));
    return *this;
}

float* Transform::getTransformResult() {
    return glm::value_ptr(transform);
}
