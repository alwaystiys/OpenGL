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


CubeIndiceTest::CubeIndiceTest() {
    triangleShader = NULL;
}

CubeIndiceTest::~CubeIndiceTest() {
    delete triangleShader;
    delete texture1;
    delete texture2;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool CubeIndiceTest::Init() {
    const char *vsFilePath = "../Shader/cube_with_color.vs";
    const char *fsFilePath = "../Shader/cube_with_color.fs";
    triangleShader = new TextureShader(NULL, NULL, vsFilePath, fsFilePath);
    if(!triangleShader->Init()) {
        return false;
    }
    //GLfloat vertices[] = {
    //    // positions          // colors           // texture coords
    //    -0.5f, -0.5f, -10.0f, //  1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right 0
    //    0.5f, -0.5f, -10.0f, //  0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right 1
    //    0.5f, -0.5f, -5.0f,  // 0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left 2
    //    -0.5f,  -0.5f, -5.0f,  // 1.0f, 1.0f, 0.0f,   0.0f, 2.0f,  // top left 3
    //    -0.5f, 0.5f, -10.0f, //  1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right 4
    //    0.5f, 0.5f, -10.0f,  // 0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right 5
    //    0.5f, 0.5f, -5.0f,  // 0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left 6
    //    -0.5f,  0.5f, -5.0f,   //1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 7
    //};
    GLfloat vertices[] = {
        //前面的正方形
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        //背面的正方形
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    //GLfloat indices[] = {
    //    // bottom
    //    0, 1, 3,
    //    3, 1, 2,
    //    // left
    //    3, 7, 4,
    //    0, 3, 4,
    //    // right
    //    6, 5, 1,
    //    6, 1, 2,
    //    // back
    //    5, 4, 0,
    //    5, 0, 1,
    //    // front
    //    7, 6, 2,
    //    7, 2, 3,
    //    // top
    //    4, 5, 6,
    //    4, 6, 7,
    //};
    GLuint indices[] = {
        0, 1, 2, 3, //前面
        0, 3, 7, 4, //左面
        5, 6, 2, 1, //右面
        7, 6, 5, 4, //后面
        3, 2, 6, 7, //上面
        1, 0, 4, 5 //地面
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
    model = model.rotate(45.0f, 1.0f, 0.0f, 0.0f);
    view = view.translate(0.0f, 0.0f, -3.0f);
    Transform projection(libmath::genPerspective(libmath::toRadians(45.0f), (float) 800 / 600, 1.0f, 100.0f));
    triangleShader->setUniformMatrix4fv("model", model.getTransformResult());
    triangleShader->setUniformMatrix4fv("view", view.getTransformResult());
    triangleShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    return true;
}

void CubeIndiceTest::RenderSceneCB() {
    triangleShader->Enable();
    glBindVertexArray(VAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
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
}

bool CubeTest::Init() {
    const char *vsFilePath = "../Shader/cube_no_color.vs";
    const char *fsFilePath = "../Shader/cube_no_color.fs";
    triangleShader = new TextureShader(NULL, NULL, vsFilePath, fsFilePath);
    if(!triangleShader->Init()) {
        return false;
    }
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    this->texture1 = new Texture("../resources/textures/container.jpg", GL_RGB);
    this->texture2 = new Texture("../resources/textures/awesomeface.png", GL_RGBA);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
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
    model = model.rotate(45.0f, 0.0f, 1.0f, 0.0f);
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
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}