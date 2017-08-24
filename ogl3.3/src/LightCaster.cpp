#include "LightCaster.h"
#include "Common/lib_transform.h"
#include <iostream>
using namespace LightCasterTest;

extern float g_cube_vertices[288];

TextureShader::TextureShader(const char *vertexShaderSource, const char *fragmentShaderSource, const char *vsFilePath, const char *fsFilePath) {
    this->vertexShaderSource = vertexShaderSource;
    this->fragmentShaderSource = fragmentShaderSource;
    this->vsFilePath = vsFilePath;
    this->fsFilePath = fsFilePath;
}

bool TextureShader::Init() {
    if(!ShaderBasic::Init()) {
        return false;
    }
    if(!AddShader(GL_VERTEX_SHADER, vsFilePath, NULL)) {
        return false;
    }
    if(!AddShader(GL_FRAGMENT_SHADER, fsFilePath, NULL)) {
        return false;
    }
    if(!LinkProgram()) {
        return false;
    }
    return true;
}

//**************************************************

LightCaster::LightCaster() :
    camera(vec3(0.0f, 0.0f, 5.0f)), lightPos(1.2f, 1.0f, 2.0f) {
    lightingShader = NULL;
    lambShader = NULL;
}

LightCaster::~LightCaster() {
    delete lightingShader;
    delete lambShader;
    delete diffuseMap;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}

bool LightCaster::Init() {
    lightingShader = new TextureShader(NULL, NULL, "../Shader/light_caster.vs", "../Shader/light_caster.fs");
    if(!lightingShader->Init()) {
        return false;
    }
    lambShader = new TextureShader(NULL, NULL, "../Shader/light_lamb_01.vs", "../Shader/light_lamb_01.fs");
    if(!lambShader->Init()) {
        return false;
    }
    cubePositions[0] = vec3(0.0f,  0.0f,  0.0f);
    cubePositions[1] = vec3(2.0f,  5.0f, -15.0f);
    cubePositions[2] = vec3(-1.5f, -2.2f, -2.5f);
    cubePositions[3] = vec3(2.4f, -0.4f, -3.5f);
    cubePositions[4] = vec3(-1.7f,  3.0f, -7.5f);
    cubePositions[5] = vec3(1.3f, -2.0f, -2.5f);
    cubePositions[6] = vec3(1.5f,  2.0f, -2.5f);
    cubePositions[7] = vec3(1.5f,  0.2f, -1.5f);
    cubePositions[8] = vec3(-1.3f,  1.0f, -1.5f);
    cubePositions[9] = vec3(-3.8f, -2.0f, -12.3f);
    diffuseMap = new Texture("../resources/textures/container2.png", GL_RGBA);
    specularMap = new Texture("../resources/textures/lighting_maps_specular_color.png", GL_RGBA);
    emissionMap = new Texture("../resources/textures/matrix.jpg", GL_RGB);
    // init cubeVAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertices), g_cube_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
    diffuseMap->Load();
    specularMap->Load();
    emissionMap->Load();
    glBindVertexArray(0);
    // inti lightVAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightingShader->Enable();
    lightingShader->setUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader->setUniform3f("lightColor",  1.0f, 1.0f, 1.0f);
    lightingShader->setUniform1i("diffuse", 0);
    lightingShader->setUniform1i("specular", 1);
    lightingShader->setUniform1i("emission", 2);
    lightingShader->setUniform1f("material.shininess", 32.0f);
    lightingShader->setUniform3f("light.ambient",  0.2f, 0.2f, 0.2f);
    lightingShader->setUniform3f("light.diffuse",  0.5f, 0.5f, 0.5f); // �����յ�����һЩ�Դ��䳡��
    lightingShader->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
    lightingShader->setUniform3f("light.direction", -0.2f, -1.0f, -0.3f);
    return true;
}

void LightCaster::RenderSceneCB() {
    //lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
    //lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
    lightingShader->Enable();
    diffuseMap->Bind(GL_TEXTURE0);
    specularMap->Bind(GL_TEXTURE1);
    emissionMap->Bind(GL_TEXTURE2);
    Transform view(camera.GetViewMatrix());
    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    lightingShader->setUniformVec3f("viewPos", camera.position);
    //lightingShader->setUniformVec3f("light.position", lightPos);
    glBindVertexArray(cubeVAO);
    for(int index = 0; index < 10; index++) {
        Transform model;
        model.translate(cubePositions[index]);
        float angle = 20.0f * index;
        model = model.rotate(libmath::toRadians(angle), 1.0f, 0.3f, 0.5f);
        lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    //lambShader->Enable();
    //lambShader->setUniformMatrix4fv("view", view.getTransformResult());
    //lambShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    //Transform model;
    //model.translate(lightPos.x, lightPos.y, lightPos.z).scale(0.2f, 0.2f, 0.2f);
    //lambShader->setUniformMatrix4fv("model", model.getTransformResult());
    //glBindVertexArray(lightVAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
}


void LightCaster::ProcessInput(KEY_PRESS isKeyPress, float delta) {
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

void LightCaster::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void LightCaster::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/


PointLightsTest::PointLightsTest() :
    camera(vec3(0.0f, 0.0f, 5.0f)), lightPos(1.2f, 1.0f, 2.0f) {
    lightingShader = NULL;
    lambShader = NULL;
}

PointLightsTest::~PointLightsTest() {
    delete lightingShader;
    delete lambShader;
    delete diffuseMap;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}



bool PointLightsTest::Init() {
    lightingShader = new TextureShader(NULL, NULL, "../Shader/point_light_caster.vs", "../Shader/point_light_caster.fs");
    if(!lightingShader->Init()) {
        return false;
    }
    lambShader = new TextureShader(NULL, NULL, "../Shader/light_lamb_01.vs", "../Shader/light_lamb_01.fs");
    if(!lambShader->Init()) {
        return false;
    }
    cubePositions[0] = vec3(0.0f,  0.0f,  0.0f);
    cubePositions[1] = vec3(2.0f,  5.0f, -15.0f);
    cubePositions[2] = vec3(-1.5f, -2.2f, -2.5f);
    cubePositions[3] = vec3(2.4f, -0.4f, -3.5f);
    cubePositions[4] = vec3(-1.7f,  3.0f, -7.5f);
    cubePositions[5] = vec3(1.3f, -2.0f, -2.5f);
    cubePositions[6] = vec3(1.5f,  2.0f, -2.5f);
    cubePositions[7] = vec3(1.5f,  0.2f, -1.5f);
    cubePositions[8] = vec3(-1.3f,  1.0f, -1.5f);
    cubePositions[9] = vec3(-3.8f, -2.0f, -12.3f);
    diffuseMap = new Texture("../resources/textures/container2.png", GL_RGBA);
    specularMap = new Texture("../resources/textures/lighting_maps_specular_color.png", GL_RGBA);
    emissionMap = new Texture("../resources/textures/matrix.jpg", GL_RGB);
    // init cubeVAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertices), g_cube_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
    diffuseMap->Load();
    specularMap->Load();
    emissionMap->Load();
    glBindVertexArray(0);
    // inti lightVAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightingShader->Enable();
    lightingShader->setUniform1i("diffuse", 0);
    lightingShader->setUniform1i("specular", 1);
    lightingShader->setUniform1i("emission", 2);
    lightingShader->setUniform3f("light.ambient",  0.2f, 0.2f, 0.2f);
    lightingShader->setUniform3f("light.diffuse",  0.5f, 0.5f, 0.5f); // �����յ�����һЩ�Դ��䳡��
    lightingShader->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
    lightingShader->setUniform1f("light.constant",  1.0f);
    lightingShader->setUniform1f("light.linear",    0.09f);
    lightingShader->setUniform1f("light.quadratic", 0.032f);
    lightingShader->setUniformVec3f("light.position", lightPos);
    //
    lightingShader->setUniform1f("material.shininess", 32.0f);
    return true;
}

void PointLightsTest::RenderSceneCB() {
    lightingShader->Enable();
    diffuseMap->Bind(GL_TEXTURE0);
    specularMap->Bind(GL_TEXTURE1);
    emissionMap->Bind(GL_TEXTURE2);
    Transform model;
    lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
    Transform view(camera.GetViewMatrix());
    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    lightingShader->setUniform3f("viewPos", camera.position.x, camera.position.y, camera.position.z);
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    for(int index = 0; index < 10; index++) {
        Transform model;
        model.translate(cubePositions[index]);
        float angle = 20.0f * index;
        model = model.rotate(libmath::toRadians(angle), 1.0f, 0.3f, 0.5f);
        lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    lambShader->Enable();
    lambShader->setUniformMatrix4fv("view", view.getTransformResult());
    lambShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    model.translate(lightPos.x, lightPos.y, lightPos.z).scale(0.2f, 0.2f, 0.2f);
    lambShader->setUniformMatrix4fv("model", model.getTransformResult());
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void PointLightsTest::ProcessInput(KEY_PRESS isKeyPress, float delta) {
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

void PointLightsTest::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void PointLightsTest::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/


SpotlightTest::SpotlightTest() :
    camera(vec3(0.0f, 0.0f, 5.0f)), lightPos(1.2f, 1.0f, 2.0f) {
    lightingShader = NULL;
    lambShader = NULL;
}

SpotlightTest::~SpotlightTest() {
    delete lightingShader;
    delete lambShader;
    delete diffuseMap;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}

bool SpotlightTest::Init() {
    lightingShader = new TextureShader(NULL, NULL, "../Shader/spot_light_caster.vs", "../Shader/spot_light_caster.fs");
    if(!lightingShader->Init()) {
        return false;
    }
    lambShader = new TextureShader(NULL, NULL, "../Shader/light_lamb_01.vs", "../Shader/light_lamb_01.fs");
    if(!lambShader->Init()) {
        return false;
    }
    cubePositions[0] = vec3(0.0f,  0.0f,  0.0f);
    cubePositions[1] = vec3(2.0f,  5.0f, -15.0f);
    cubePositions[2] = vec3(-1.5f, -2.2f, -2.5f);
    cubePositions[3] = vec3(2.4f, -0.4f, -3.5f);
    cubePositions[4] = vec3(-1.7f,  3.0f, -7.5f);
    cubePositions[5] = vec3(1.3f, -2.0f, -2.5f);
    cubePositions[6] = vec3(1.5f,  2.0f, -2.5f);
    cubePositions[7] = vec3(1.5f,  0.2f, -1.5f);
    cubePositions[8] = vec3(-1.3f,  1.0f, -1.5f);
    cubePositions[9] = vec3(-3.8f, -2.0f, -12.3f);
    diffuseMap = new Texture("../resources/textures/container2.png", GL_RGBA);
    specularMap = new Texture("../resources/textures/lighting_maps_specular_color.png", GL_RGBA);
    emissionMap = new Texture("../resources/textures/matrix.jpg", GL_RGB);
    // init cubeVAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertices), g_cube_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
    diffuseMap->Load();
    specularMap->Load();
    emissionMap->Load();
    glBindVertexArray(0);
    // inti lightVAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightingShader->Enable();
    lightingShader->setUniform1i("diffuse", 0);
    lightingShader->setUniform1i("specular", 1);
    lightingShader->setUniform1i("emission", 2);
    lightingShader->setUniform3f("light.ambient",  0.2f, 0.2f, 0.2f);
    lightingShader->setUniform3f("light.diffuse",  0.5f, 0.5f, 0.5f); // �����յ�����һЩ�Դ��䳡��
    lightingShader->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
    lightingShader->setUniform1f("light.constant",  1.0f);
    lightingShader->setUniform1f("light.linear",    0.09f);
    lightingShader->setUniform1f("light.quadratic", 0.032f);
    lightingShader->setUniformVec3f("light.position", lightPos);
    //
    lightingShader->setUniform1f("material.shininess", 32.0f);
    return true;
}

void SpotlightTest::RenderSceneCB() {
    lightingShader->Enable();
    diffuseMap->Bind(GL_TEXTURE0);
    specularMap->Bind(GL_TEXTURE1);
    emissionMap->Bind(GL_TEXTURE2);
    Transform model;
    lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
    Transform view(camera.GetViewMatrix());
    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    lightingShader->setUniform3f("viewPos", camera.position.x, camera.position.y, camera.position.z);
    lightingShader->setUniformVec3f("light.direction", camera.front);
    lightingShader->setUniform1f("light.cutOff", glm::cos(glm::radians(12.5f)));
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    for(int index = 0; index < 10; index++) {
        Transform model;
        model.translate(cubePositions[index]);
        float angle = 20.0f * index;
        model = model.rotate(libmath::toRadians(angle), 1.0f, 0.3f, 0.5f);
        lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    lambShader->Enable();
    lambShader->setUniformMatrix4fv("view", view.getTransformResult());
    lambShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    model.translate(lightPos.x, lightPos.y, lightPos.z).scale(0.2f, 0.2f, 0.2f);
    lambShader->setUniformMatrix4fv("model", model.getTransformResult());
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SpotlightTest::ProcessInput(KEY_PRESS isKeyPress, float delta) {
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

void SpotlightTest::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void SpotlightTest::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

BetterSpotlightTest::BetterSpotlightTest() :
    camera(vec3(0.0f, 0.0f, 5.0f)), lightPos(1.2f, 1.0f, 2.0f) {
    lightingShader = NULL;
    lambShader = NULL;
}

BetterSpotlightTest::~BetterSpotlightTest() {
    delete lightingShader;
    delete lambShader;
    delete diffuseMap;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}

bool BetterSpotlightTest::Init() {
    lightingShader = new TextureShader(NULL, NULL, "../Shader/spot_light_caster_02.vs", "../Shader/spot_light_caster_02.fs");
    if(!lightingShader->Init()) {
        return false;
    }
    lambShader = new TextureShader(NULL, NULL, "../Shader/light_lamb_01.vs", "../Shader/light_lamb_01.fs");
    if(!lambShader->Init()) {
        return false;
    }
    cubePositions[0] = vec3(0.0f,  0.0f,  0.0f);
    cubePositions[1] = vec3(2.0f,  5.0f, -15.0f);
    cubePositions[2] = vec3(-1.5f, -2.2f, -2.5f);
    cubePositions[3] = vec3(2.4f, -0.4f, -3.5f);
    cubePositions[4] = vec3(-1.7f,  3.0f, -7.5f);
    cubePositions[5] = vec3(1.3f, -2.0f, -2.5f);
    cubePositions[6] = vec3(1.5f,  2.0f, -2.5f);
    cubePositions[7] = vec3(1.5f,  0.2f, -1.5f);
    cubePositions[8] = vec3(-1.3f,  1.0f, -1.5f);
    cubePositions[9] = vec3(-3.8f, -2.0f, -12.3f);
    diffuseMap = new Texture("../resources/textures/container2.png", GL_RGBA);
    specularMap = new Texture("../resources/textures/lighting_maps_specular_color.png", GL_RGBA);
    emissionMap = new Texture("../resources/textures/matrix.jpg", GL_RGB);
    // init cubeVAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertices), g_cube_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
    diffuseMap->Load();
    specularMap->Load();
    emissionMap->Load();
    glBindVertexArray(0);
    // inti lightVAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightingShader->Enable();
    lightingShader->setUniform1i("diffuse", 0);
    lightingShader->setUniform1i("specular", 1);
    lightingShader->setUniform1i("emission", 2);
    lightingShader->setUniform3f("light.ambient",  0.2f, 0.2f, 0.2f);
    lightingShader->setUniform3f("light.diffuse",  0.5f, 0.5f, 0.5f); // �����յ�����һЩ�Դ��䳡��
    lightingShader->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
    lightingShader->setUniform1f("light.constant",  1.0f);
    lightingShader->setUniform1f("light.linear",    0.09f);
    lightingShader->setUniform1f("light.quadratic", 0.032f);
    lightingShader->setUniformVec3f("light.position", lightPos);
    lightingShader->setUniform1f("light.cutOff", glm::cos(glm::radians(12.5f)));
    lightingShader->setUniform1f("light.outerCutOff", glm::cos(glm::radians(17.5f)));
    //
    lightingShader->setUniform1f("material.shininess", 32.0f);
    return true;
}

void BetterSpotlightTest::RenderSceneCB() {
    lightingShader->Enable();
    diffuseMap->Bind(GL_TEXTURE0);
    specularMap->Bind(GL_TEXTURE1);
    emissionMap->Bind(GL_TEXTURE2);
    Transform model;
    lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
    Transform view(camera.GetViewMatrix());
    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    lightingShader->setUniform3f("viewPos", camera.position.x, camera.position.y, camera.position.z);
    lightingShader->setUniformVec3f("light.direction", camera.front);
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    for(int index = 0; index < 10; index++) {
        Transform model;
        model.translate(cubePositions[index]);
        float angle = 20.0f * index;
        model = model.rotate(libmath::toRadians(angle), 1.0f, 0.3f, 0.5f);
        lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    lambShader->Enable();
    lambShader->setUniformMatrix4fv("view", view.getTransformResult());
    lambShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    model.translate(lightPos.x, lightPos.y, lightPos.z).scale(0.2f, 0.2f, 0.2f);
    lambShader->setUniformMatrix4fv("model", model.getTransformResult());
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void BetterSpotlightTest::ProcessInput(KEY_PRESS isKeyPress, float delta) {
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

void BetterSpotlightTest::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void BetterSpotlightTest::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}