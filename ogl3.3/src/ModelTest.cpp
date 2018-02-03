#include "ModelTest.h"
#include "Common/lib_transform.h"

ModelTest::ModelTest() :
    camera(vec3(0.0f, 0.0f, 5.0f)), playModel("../resources/objects/nanosuit/nanosuit.obj") {
    modelShader = NULL;
}

ModelTest::~ModelTest() {
    delete modelShader;
    //glDeleteVertexArrays(1, &cubeVAO);
    //glDeleteVertexArrays(1, &lightVAO);
    //glDeleteBuffers(1, &VBO);
}

bool ModelTest::Init() {
    modelShader = new CommonShader(NULL, NULL, "../Shader/1.model_loading.vs", "../Shader/1.model_loading.fs");
    if(!modelShader->Init()) {
        return false;
    }

    return true;
}

void ModelTest::RenderSceneCB() {
	modelShader->Enable();

    //// view/projection transformations
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    modelShader->setUniformMatrix4fv("projection", projection.getTransformResult());
	Transform view(camera.GetViewMatrix());
    modelShader->setUniformMatrix4fv("view", view.getTransformResult());

    //// render the loaded model
    Transform model;
	model = model.translate(0.0f, -1.75f, 0.0f).scale(0.2f, 0.2f, 0.2f);
	modelShader->setUniformMatrix4fv("model", model.getTransformResult());
    playModel.Draw(*modelShader);

}


void ModelTest::ProcessInput(KEY_PRESS isKeyPress, float delta) {
    if(isKeyPress(GLFW_KEY_W)) {
        camera.processKeyboard(FORWARD, delta);
    }
    if(isKeyPress(GLFW_KEY_S)) {
        camera.processKeyboard(BACKWARD, delta);
    }
    if(isKeyPress(GLFW_KEY_A)) {
        camera.processKeyboard(LEFT, delta);
    }
    if(isKeyPress(GLFW_KEY_D)) {
        camera.processKeyboard(RIGHT, delta);
    }
}

void ModelTest::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void ModelTest::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}