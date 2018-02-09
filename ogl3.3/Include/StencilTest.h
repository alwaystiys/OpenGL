#ifndef STENCIL_TEST_H
#define STENCIL_TEST_H

#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/common_shader.h"
#include "Common/lib_transform.h"
#include "Common/lib_math.h"
#include "Common/lib_camera.h"

namespace StencilTest {

/************************************************************************/
/* Ä£°å²âÊÔ                                                             */
/************************************************************************/
class StencilTesting : public CommonCallbacks {
public:
    StencilTesting();
    ~StencilTesting();
    virtual void GLClearConfig();
    virtual void PreRenderConfig();
    virtual bool Init();
    virtual void RenderSceneCB();
private:
    GLuint VBO, planeVBO, cubeVAO, planeVAO;
    CommonShader *m_shader, *m_outline_shader;
    Texture *cubeTexture, *floorTexture;
};
}

#endif STENCIL_TEST_H
