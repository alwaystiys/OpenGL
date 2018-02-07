//#include "AdvanceTest.h"
//
//using namespace AdvanceTest;
///************************************************************************/
///* 深度测试                                                             */
///************************************************************************/
//extern float g_cube_notex_vertices[288];
//extern float g_plane_vertices[30];
//
//DepthTesting::DepthTesting() :
//    camera(vec3(0.0f, 0.0f, 5.0f)), lightPos(1.2f, 1.0f, 2.0f) {
//    lightingShader = NULL;
//}
//
//DepthTesting::~DepthTesting() {
//    delete lightingShader;
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &lightVAO);
//    glDeleteBuffers(1, &VBO);
//}
//
//bool DepthTesting::Init() {
//    lightingShader = new CommonShader(NULL, NULL, "../Shader/depth_testing.vs", "../Shader/depth_testing.fs");
//    if(!lightingShader->Init()) {
//        return false;
//    }
//    // init cubeVAO
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_notex_vertices), g_cube_notex_vertices, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
//    glEnableVertexAttribArray(1);
//    glBindVertexArray(0);
//    // init planeVAO
//    glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//
//
//    glBindVertexArray(0);
//    //lightingShader->Enable();
//    //lightingShader->setUniform1i("diffuse", 0);
//    //lightingShader->setUniform1i("specular", 1);
//    //lightingShader->setUniform1i("emission", 2);
//    //lightingShader->setUniform3f("light.ambient",  0.2f, 0.2f, 0.2f);
//    //lightingShader->setUniform3f("light.diffuse",  0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
//    //lightingShader->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
//    //lightingShader->setUniform1f("light.constant",  1.0f);
//    //lightingShader->setUniform1f("light.linear",    0.09f);
//    //lightingShader->setUniform1f("light.quadratic", 0.032f);
//    //lightingShader->setUniformVec3f("light.position", lightPos);
//    //lightingShader->setUniform1f("light.cutOff", glm::cos(glm::radians(12.5f)));
//    //lightingShader->setUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));
//    ////
//    //lightingShader->setUniform1f("material.shininess", 32.0f);
//    return true;
//}
//
//void DepthTesting::RenderSceneCB() {
//    lightingShader->Enable();
//    diffuseMap->Bind(GL_TEXTURE0);
//    Transform model;
//    lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
//    Transform view(camera.GetViewMatrix());
//    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
//    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
//    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
//    lightingShader->setUniform3f("viewPos", camera.position.x, camera.position.y, camera.position.z);
//    lightingShader->setUniformVec3f("light.direction", camera.front);
//    glBindVertexArray(cubeVAO);
//    for(int index = 0; index < 10; index++) {
//        Transform model;
//        model.translate(cubePositions[index]);
//        float angle = 20.0f * index;
//        model = model.rotate(libmath::toRadians(angle), 1.0f, 0.3f, 0.5f);
//        lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//    }
//}
//
//void DepthTesting::ProcessInput(KEY_PRESS isKeyPress, float delta) {
//    if(isKeyPress(GLFW_KEY_W)) {
//        camera.processKeyboard(FORWARD, delta);
//    }
//    if(isKeyPress(GLFW_KEY_S)) {
//        camera.processKeyboard(BACKWARD, delta);
//    }
//    if(isKeyPress(GLFW_KEY_A)) {
//        camera.processKeyboard(LEFT, delta);
//    }
//    if(isKeyPress(GLFW_KEY_D)) {
//        camera.processKeyboard(RIGHT, delta);
//    }
//}
//
//void DepthTesting::PorcessMouseInput(float delta, double xpos, double ypos) {
//    camera.processMouseMovement(delta, xpos, ypos);
//}
//void DepthTesting::PorcessScrollInput(float delta, double xoffset, double yoffset) {
//    camera.processMouseScroll(delta, xoffset, yoffset);
//}