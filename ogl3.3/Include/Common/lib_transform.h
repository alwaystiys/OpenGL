
#ifndef LIB_TRANSFORM_H
#define LIB_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Transform {

public:
    Transform();
    ~Transform();
    Transform& translate(float x, float y, float z);
    Transform& rotate(float angle, float x, float y, float z);
    Transform& scale();
    float* getTransformResult();

private:
    glm::mat4 transform;


};


#endif LIB_TRANSFORM_H



