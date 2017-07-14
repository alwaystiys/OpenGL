#include "Common/lib_math.h"

namespace libmath {

float toRadians(float value) {
    return glm::radians(value);
}

mat4 genLookAtMatrix(vec3 cameraPos, vec3 targetPos, vec3 upPos) {
    return glm::lookAt(cameraPos, targetPos, upPos);
}

vec3 cross(vec3 v1, vec3 v2) {
    return glm::cross(v1, v2);
}

vec3 normalize(vec3 v) {
    return glm::normalize(v);
}


}
