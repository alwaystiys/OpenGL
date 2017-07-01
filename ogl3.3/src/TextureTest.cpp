#include "TextureTest.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Common/stb_image.h"

TextureShader::TextureShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
    this->vertexShaderSource = vertexShaderSource;
    this->fragmentShaderSource = fragmentShaderSource;
}

bool TextureShader::Init() {
    if(!ShaderBasic::Init()) {
        return false;
    }
    if(!AddShader(GL_VERTEX_SHADER, "../Shader/simple_texture_test.vs", NULL)) {
        return false;
    }
    if(!AddShader(GL_FRAGMENT_SHADER, "../Shader/simple_texture_test.fs", NULL)) {
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
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

bool SimpleTexture::Init() {
    triangleShader = new TextureShader(NULL, NULL);
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
    GLuint texture;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenTextures(1, &texture);
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
    glBindTexture(GL_TEXTURE_2D, texture);
    // wrap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLint width, height, nrChannels;
    unsigned char *data = stbi_load("../resources/textures/container.jpg", &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindVertexArray(0);
    return true;
}

void SimpleTexture::RenderSceneCB() {
    //std::cout << "RenderSceneCB" << std::endl;
    triangleShader->Enable();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


