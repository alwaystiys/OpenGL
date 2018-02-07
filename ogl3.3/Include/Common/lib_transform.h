
#ifndef LIB_TRANSFORM_H
#define LIB_TRANSFORM_H

#include "Common/lib_math.h"


class Transform {

public:
    Transform();
    Transform(mat4 matrix);
    ~Transform();
    Transform& translate(vec3);
    Transform& translate(float x, float y, float z);
    Transform& rotate(float angle, float x, float y, float z);
    Transform& scale(float x, float y, float z);
    float* getTransformResult();
	void reset();

private:
    mat4 transform;


};


#endif LIB_TRANSFORM_H



