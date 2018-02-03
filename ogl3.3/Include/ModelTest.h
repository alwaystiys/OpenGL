#ifndef MODEL_TEST_H
#define MODEL_TEST_H

#include "Common/app_callbacks.h"
#include "Common/lib_texture.h"
#include "Common/common_shader.h"
#include "Common/lib_math.h"
#include "Common/lib_camera.h"
#include "Common/lib_model.h"

class ModelTest : public ICallbacks {

public:
    ModelTest();
    ~ModelTest();
    virtual bool Init();
    virtual void RenderSceneCB();
    virtual void ProcessInput(KEY_PRESS, float);
    virtual void PorcessMouseInput(float, double, double);
    virtual void PorcessScrollInput(float, double, double);

private:
    Camera camera;
	Model playModel;
    //GLuint VBO, cubeVAO, lightVAO;
    CommonShader *modelShader;
};

#endif MODEL_TEST_H