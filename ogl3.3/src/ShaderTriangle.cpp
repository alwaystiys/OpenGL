#include "ShaderTriangle.h"




InnterShader::InnterShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
    this->vertexShaderSource = vertexShaderSource;
    this->fragmentShaderSource = fragmentShaderSource;
}

bool InnterShader::Init() {
    if(!ShaderBasic::Init()) {
        return false;
    }
    if(!AddShader(GL_VERTEX_SHADER, NULL, vertexShaderSource)) {
        return false;
    }
    if(!AddShader(GL_FRAGMENT_SHADER, NULL, fragmentShaderSource)) {
        return false;
    }
    if(!LinkProgram()) {
        return false;
    }
    return true;
}

//****************************************************

UniformTriangle::UniformTriangle() {
    triangleShader = NULL;
}

UniformTriangle::~UniformTriangle() {
    delete triangleShader;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

bool UniformTriangle::Init() {
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "out vec4 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos, 1.0);\n"
                                     "	 vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 把输出变量设置为暗红色\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec4 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vertexColor;\n"
                                       "}\n\0";
    triangleShader = new InnterShader(vertexShaderSource, fragmentShaderSource);
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

void UniformTriangle::RenderSceneCB() {
    //std::cout << "RenderSceneCB" << std::endl;
    triangleShader->Enable();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
