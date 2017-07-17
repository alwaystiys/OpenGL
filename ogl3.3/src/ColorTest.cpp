#include "ColorTest.h"
#include "Common/lib_transform.h"
#include <iostream>
using namespace ColorTest;

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
    Transform view(camera.GetViewMatrix());
    lightingShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    lightingShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    float angle = 20.0f;
    Transform model;
    model.rotate(libmath::toRadians(angle), 1.0f, 1.0f, 1.0f);
    lightingShader->setUniformMatrix4fv("model", model.getTransformResult());
    glBindVertexArray(cubeVAO);
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
