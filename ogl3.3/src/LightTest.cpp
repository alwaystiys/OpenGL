#include "LightTest.h"
#include "Common/lib_transform.h"
#include <iostream>
using namespace LightTest;

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

FPS2Test::FPS2Test() :
    camera(vec3(0.0f, 0.0f, 3.0f)) {
    lightingShader = NULL;
    lambShader = NULL;
}

FPS2Test::~FPS2Test() {
    delete lightingShader;
    delete lambShader;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}

bool FPS2Test::Init() {
    lightingShader = new TextureShader(NULL, NULL, "../Shader/light_cube_01.vs", "../Shader/light_cube_01.fs");
    if(!lightingShader->Init()) {
        return false;
    }
    lambShader = new TextureShader(NULL, NULL, "../Shader/light_lamb_01.vs", "../Shader/light_lamb_01.fs");
    if(!lambShader->Init()) {
        return false;
    }
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    // init cubeVAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    // inti lightVAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightingShader->Enable();
    lightingShader->setUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader->setUniform3f("lightColor",  1.0f, 1.0f, 1.0f);
    return true;
}

void FPS2Test::RenderSceneCB() {
    lightingShader->Enable();
    Transform model;
    lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
    Transform view(camera.GetViewMatrix());
    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    lambShader->Enable();
    lambShader->setUniformMatrix4fv("view", view.getTransformResult());
    lambShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    model.translate(1.2f, 1.0f, 2.0f).scale(0.2f, 0.2f, 0.2f);
    lambShader->setUniformMatrix4fv("model", model.getTransformResult());
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void FPS2Test::ProcessInput(KEY_PRESS isKeyPress, float delta) {
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

void FPS2Test::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void FPS2Test::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}

//**************************************************

BasicLightTest::BasicLightTest() :
    camera(vec3(0.0f, 0.0f, 5.0f)), lightPos(1.2f, 1.0f, 2.0f) {
    lightingShader = NULL;
    lambShader = NULL;
}

BasicLightTest::~BasicLightTest() {
    delete lightingShader;
    delete lambShader;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}

bool BasicLightTest::Init() {
    lightingShader = new TextureShader(NULL, NULL, "../Shader/light_gouraud_cube_02.vs", "../Shader/light_gouraud_cube_02.fs");
    //lightingShader = new TextureShader(NULL, NULL, "../Shader/light_cube_02.vs", "../Shader/light_cube_02.fs");
    if(!lightingShader->Init()) {
        return false;
    }
    lambShader = new TextureShader(NULL, NULL, "../Shader/light_lamb_01.vs", "../Shader/light_lamb_01.fs");
    if(!lambShader->Init()) {
        return false;
    }
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // init cubeVAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    // inti lightVAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightingShader->Enable();
    lightingShader->setUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader->setUniform3f("lightColor",  1.0f, 1.0f, 1.0f);
    return true;
}

void BasicLightTest::RenderSceneCB() {
    //lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
    //lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
    lightingShader->Enable();
    Transform model;
    lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
    Transform view(camera.GetViewMatrix());
    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    lightingShader->setUniform3f("viewPos", camera.position.x, camera.position.y, camera.position.z);
    lightingShader->setUniformVec3f("lightPos", lightPos);
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    lambShader->Enable();
    lambShader->setUniformMatrix4fv("view", view.getTransformResult());
    lambShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    model.translate(lightPos.x, lightPos.y, lightPos.z).scale(0.2f, 0.2f, 0.2f);
    lambShader->setUniformMatrix4fv("model", model.getTransformResult());
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void BasicLightTest::ProcessInput(KEY_PRESS isKeyPress, float delta) {
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

void BasicLightTest::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void BasicLightTest::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}


//**************************************************

MaterialTest::MaterialTest() :
    camera(vec3(0.0f, 0.0f, 5.0f)), lightPos(1.2f, 1.0f, 2.0f) {
    lightingShader = NULL;
    lambShader = NULL;
}

MaterialTest::~MaterialTest() {
    delete lightingShader;
    delete lambShader;
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}

bool MaterialTest::Init() {
    lightingShader = new TextureShader(NULL, NULL, "../Shader/light_material_cube.vs", "../Shader/light_material_cube.fs");
    if(!lightingShader->Init()) {
        return false;
    }
    lambShader = new TextureShader(NULL, NULL, "../Shader/light_lamb_01.vs", "../Shader/light_lamb_01.fs");
    if(!lambShader->Init()) {
        return false;
    }
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // init cubeVAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    // inti lightVAO
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    lightingShader->Enable();
    lightingShader->setUniform3f("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader->setUniform3f("lightColor",  1.0f, 1.0f, 1.0f);
    lightingShader->setUniform3f("material.ambient",  1.0f, 0.5f, 0.31f);
    lightingShader->setUniform3f("material.diffuse",  1.0f, 0.5f, 0.31f);
    lightingShader->setUniform3f("material.specular", 0.5f, 0.5f, 0.5f);
    lightingShader->setUniform1f("material.shininess", 32.0f);
    lightingShader->setUniform3f("light.ambient",  0.2f, 0.2f, 0.2f);
    lightingShader->setUniform3f("light.diffuse",  0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
    lightingShader->setUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
    return true;
}

void MaterialTest::RenderSceneCB() {
    //lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
    //lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
    lightingShader->Enable();
    Transform model;
    lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
    Transform view(camera.GetViewMatrix());
    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    lightingShader->setUniform3f("viewPos", camera.position.x, camera.position.y, camera.position.z);
    lightingShader->setUniformVec3f("lightPos", lightPos);
    vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);
    vec3 diffuseColor = lightColor   * vec3(0.5f); // 降低影响
    vec3 ambientColor = diffuseColor * vec3(0.2f); // 很低的影响
    lightingShader->setUniformVec3f("light.ambient",  ambientColor);
    lightingShader->setUniformVec3f("light.diffuse",  diffuseColor); // 将光照调暗了一些以搭配场景
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    lambShader->Enable();
    lambShader->setUniformMatrix4fv("view", view.getTransformResult());
    lambShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    model.translate(lightPos.x, lightPos.y, lightPos.z).scale(0.2f, 0.2f, 0.2f);
    lambShader->setUniformMatrix4fv("model", model.getTransformResult());
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void MaterialTest::ProcessInput(KEY_PRESS isKeyPress, float delta) {
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

void MaterialTest::PorcessMouseInput(float delta, double xpos, double ypos) {
    camera.processMouseMovement(delta, xpos, ypos);
}
void MaterialTest::PorcessScrollInput(float delta, double xoffset, double yoffset) {
    camera.processMouseScroll(delta, xoffset, yoffset);
}
