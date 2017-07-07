#include "CoordinateTest.h"
#include "Common/lib_transform.h"
#include "Common/lib_math.h"
#include <iostream>

using namespace CoordinateTest;

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


MultipleTexture::MultipleTexture() {
    triangleShader = NULL;
}

MultipleTexture::~MultipleTexture() {
    delete triangleShader;
    delete texture1;
    delete texture2;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool MultipleTexture::Init() {
    const char *vsFilePath = "../Shader/multi_texture_coordinate_test.vs";
    const char *fsFilePath = "../Shader/multi_texture_test.fs";
    triangleShader = new TextureShader(NULL, NULL, vsFilePath, fsFilePath);
    if(!triangleShader->Init()) {
        return false;
    }
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left
    };
    GLuint indices[] = {
        3, 0, 1,
        1, 2, 3,
    };
    this->texture1 = new Texture("../resources/textures/container.jpg", GL_RGB);
    this->texture2 = new Texture("../resources/textures/awesomeface.png", GL_RGBA);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    this->texture1->Load();
    this->texture2->setLoadFlipVertically();
    this->texture2->Load();
    glBindVertexArray(0);
    triangleShader->Enable();
    triangleShader->setUniform1i("ourTexture1", 0);
    triangleShader->setUniform1i("ourTexture2", 1);
    this->texture1->Bind(GL_TEXTURE0);
    this->texture2->Bind(GL_TEXTURE1);
    Transform model, view;
    model = model.rotate(libmath::toRadians(-55.0f), 1.0f, 0.0f, 0.0f);
    view = view.translate(0.0f, 0.0f, -3.0f);
    Transform projection(libmath::genPerspective(libmath::toRadians(45.0f), (float) 800 / 600, 1.0f, 100.0f));
    triangleShader->setUniformMatrix4fv("model", model.getTransformResult());
    triangleShader->setUniformMatrix4fv("view", view.getTransformResult());
    triangleShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    return true;
}

void MultipleTexture::RenderSceneCB() {
    triangleShader->Enable();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

//**************************************************


CubeTest::CubeTest() {
    triangleShader = NULL;
}

CubeTest::~CubeTest() {
    delete triangleShader;
    delete texture1;
    delete texture2;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool CubeTest::Init() {
    const char *vsFilePath = "../Shader/multi_texture_coordinate_test.vs";
    const char *fsFilePath = "../Shader/multi_texture_test.fs";
    triangleShader = new TextureShader(NULL, NULL, vsFilePath, fsFilePath);
    if(!triangleShader->Init()) {
        return false;
    }
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left
    };
    GLuint indices[] = {
        3, 0, 1,
        1, 2, 3,
    };
    this->texture1 = new Texture("../resources/textures/container.jpg", GL_RGB);
    this->texture2 = new Texture("../resources/textures/awesomeface.png", GL_RGBA);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    this->texture1->Load();
    this->texture2->setLoadFlipVertically();
    this->texture2->Load();
    glBindVertexArray(0);
    triangleShader->Enable();
    triangleShader->setUniform1i("ourTexture1", 0);
    triangleShader->setUniform1i("ourTexture2", 1);
    this->texture1->Bind(GL_TEXTURE0);
    this->texture2->Bind(GL_TEXTURE1);
    Transform model, view;
    model = model.rotate(libmath::toRadians(-55.0f), 1.0f, 0.0f, 0.0f);
    view = view.translate(0.0f, 0.0f, -3.0f);
    Transform projection(libmath::genPerspective(libmath::toRadians(45.0f), (float) 800 / 600, 1.0f, 100.0f));
    triangleShader->setUniformMatrix4fv("model", model.getTransformResult());
    triangleShader->setUniformMatrix4fv("view", view.getTransformResult());
    triangleShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    return true;
}

void CubeTest::RenderSceneCB() {
    triangleShader->Enable();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}