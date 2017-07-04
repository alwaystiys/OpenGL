#include "TextureTest.h"
#include <iostream>

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

//****************************************

SimpleTexture::SimpleTexture() {
    triangleShader = NULL;
}

SimpleTexture::~SimpleTexture() {
    delete triangleShader;
    delete texture;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool SimpleTexture::Init() {
    const char *vsFilePath = "../Shader/simple_texture_test.vs";
    const char *fsFilePath = "../Shader/simple_texture_test.fs";
    triangleShader = new TextureShader(NULL, NULL, vsFilePath, fsFilePath);
    if(!triangleShader->Init()) {
        return false;
    }
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    GLuint indices[] = {
        3, 0, 1,
        1, 2, 3,
    };
    texture = new Texture("../resources/textures/container.jpg", GL_RGB);
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
    texture->Load();
    glBindVertexArray(0);
    return true;
}

void SimpleTexture::RenderSceneCB() {
    triangleShader->Enable();
    texture->Bind(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


//****************************************

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
    const char *vsFilePath = "../Shader/simple_texture_test.vs";
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
    return true;
}

void MultipleTexture::RenderSceneCB() {
    triangleShader->Enable();
    this->texture1->Bind(GL_TEXTURE0);
    this->texture2->Bind(GL_TEXTURE1);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
