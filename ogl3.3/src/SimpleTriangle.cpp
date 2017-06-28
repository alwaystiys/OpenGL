#include "SimpleTriangle.h"

TriangleShader::TriangleShader() {
}

bool TriangleShader::Init() {
    if(!ShaderBasic::Init()) {
        return false;
    }
    if(!AddShader(GL_VERTEX_SHADER, "../Shader/triangle.vs", NULL)) {
        return false;
    }
    if(!AddShader(GL_FRAGMENT_SHADER, "../Shader/triangle.fs", NULL)) {
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


//****************************************************************


AppIndexTriangle::AppIndexTriangle() {
    triangleShader = NULL;
}

AppIndexTriangle::~AppIndexTriangle() {
    delete triangleShader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

bool AppIndexTriangle::Init() {
    triangleShader = new TriangleShader();
    if(!triangleShader->Init()) {
        return false;
    }
    //std::cout << "Init" << std::endl;
    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return true;
}

void AppIndexTriangle::RenderSceneCB() {
    //std::cout << "RenderSceneCB" << std::endl;
    triangleShader->Enable();
    glBindVertexArray(VAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}