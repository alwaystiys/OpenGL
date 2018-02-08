#ifndef DEPTH_TEST_H
#define DEPTH_TEST_H

#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/common_shader.h"
#include "Common/lib_transform.h"
#include "Common/lib_math.h"
#include "Common/lib_camera.h"

namespace DepthTest {

/************************************************************************/
/* …Ó∂»≤‚ ‘                                                             */
/************************************************************************/
class DepthTesting : public CommonCallbacks {
public:
    DepthTesting();
    ~DepthTesting();
    virtual bool Init();
    virtual void PreRenderConfig();
    virtual void RenderSceneCB();
private:
    GLuint VBO, planeVBO, cubeVAO, planeVAO;
    CommonShader *m_shader;
    Texture *cubeTexture, *floorTexture;
};
}

#endif DEPTH_TEST_H
