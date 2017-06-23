#include "AppTriangle.h"

TriangleShader::TriangleShader() {
}

bool TriangleShader::Init() {
    if(!ShaderBasic::Init()) {
        return false;
    }
    if(!AddShader(GL_VERTEX_SHADER, "../Shader/triangle.vs")) {
        return false;
    }
    if(!AddShader(GL_FRAGMENT_SHADER, "../Shader/triangle.fs")) {
        return false;
    }
    if(!LinkProgram()) {
        return false;
    }
    return true;
}

//****************************************************

AppTriangle::AppTriangle() {
    triangleShader = NULL;
}

AppTriangle::~AppTriangle() {
    delete triangleShader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

bool AppTriangle::Init() {
    triangleShader = new TriangleShader();
    if(!triangleShader->Init()) {
        return false;
    }
    //std::cout << "Init" << std::endl;
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f, // right
        0.0f,  0.5f, 0.0f  // top
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
}

void AppTriangle::RenderSceneCB() {
    //std::cout << "RenderSceneCB" << std::endl;
    triangleShader->Enable();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
