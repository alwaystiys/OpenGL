#ifndef LIB_MATH_H
#define LIB_MATH_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/************************************************************************/
/*
1、封装了glm
2、常用的数学操作
*/
/************************************************************************/
typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::mat4 mat4;

namespace libmath {

float toRadians(float value);
template<typename T> glm::mat4 genPerspective(T fovy, T aspect, T near, T far) {
    return glm::perspective(fovy, aspect, near, far);
}

mat4 genLookAtMatrix(vec3, vec3, vec3);
vec3 cross(vec3, vec3);
vec3 normalize(vec3);
}






#endif LIB_MATH_H