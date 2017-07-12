
#ifndef LIB_TRANSFORM_H
#define LIB_TRANSFORM_H

#include "Common/lib_math.h"


class Transform {

public:
    Transform();
    Transform(glm::mat4 matrix);
    ~Transform();
    Transform& translate(float x, float y, float z);
    Transform& rotate(float angle, float x, float y, float z);
    Transform& scale(float x, float y, float z);
    float* getTransformResult();

private:
    glm::mat4 transform;


};


#endif LIB_TRANSFORM_H



