#include "CameraTest.h"
#include "Common/lib_transform.h"
#include <iostream>

using namespace CameraTest;

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


MutitudeCubeTest::MutitudeCubeTest() {
    triangleShader = NULL;
}

MutitudeCubeTest::~MutitudeCubeTest() {
    delete triangleShader;
    delete texture1;
    delete texture2;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

bool MutitudeCubeTest::Init() {
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
    // world space positions of our cubes
    cubePositions[0] = vec3(0.0f,  0.0f,  0.0f);
    cubePositions[1] = vec3(2.0f,  5.0f, -15.0f);
    cubePositions[2] = vec3(-1.5f, -2.2f, -2.5f);
    cubePositions[3] = vec3(-3.8f, -2.0f, -12.3f);
    cubePositions[4] = vec3(2.4f, -0.4f, -3.5f);
    cubePositions[5] = vec3(-1.7f,  3.0f, -7.5f);
    cubePositions[6] = vec3(1.3f, -2.0f, -2.5f);
    cubePositions[7] = vec3(1.5f,  2.0f, -2.5f);
    cubePositions[8] = vec3(1.5f,  0.2f, -1.5f);
    cubePositions[9] = vec3(-1.3f,  1.0f, -1.5f);
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
    Transform projection(libmath::genPerspective(libmath::toRadians(45.0f), (float) 800 / 600, 1.0f, 100.0f));
    triangleShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    return true;
}

void MutitudeCubeTest::RenderSceneCB() {
    triangleShader->Enable();
    //view = view.translate(0.0f, 0.0f, -3.0f);
    float radius = 10.0f;
    float camX   = sin(glfwGetTime()) * radius;
    float camZ   = cos(glfwGetTime()) * radius;
    Transform view(libmath::genLookAtMatrix(vec3(camX, 0.0f, camZ), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)));
    triangleShader->setUniformMatrix4fv("view", view.getTransformResult());
    glBindVertexArray(VAO);
    for(unsigned int i = 0; i < 10; i++) {
        Transform model;
        model = model
                .translate(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z)
                .rotate(libmath::toRadians(50.0f), 1.0f, 1.0f, 1.0f);
        triangleShader->setUniformMatrix4fv("model", model.getTransformResult());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


//**************************************************


FPSTest::FPSTest() {
    triangleShader = NULL;
}

FPSTest::~FPSTest() {
    delete triangleShader;
    delete texture1;
    delete texture2;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

bool FPSTest::Init() {
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
    // world space positions of our cubes
    cubePositions[0] = vec3(0.0f,  0.0f,  0.0f);
    cubePositions[1] = vec3(2.0f,  5.0f, -15.0f);
    cubePositions[2] = vec3(-1.5f, -2.2f, -2.5f);
    cubePositions[3] = vec3(-3.8f, -2.0f, -12.3f);
    cubePositions[4] = vec3(2.4f, -0.4f, -3.5f);
    cubePositions[5] = vec3(-1.7f,  3.0f, -7.5f);
    cubePositions[6] = vec3(1.3f, -2.0f, -2.5f);
    cubePositions[7] = vec3(1.5f,  2.0f, -2.5f);
    cubePositions[8] = vec3(1.5f,  0.2f, -1.5f);
    cubePositions[9] = vec3(-1.3f,  1.0f, -1.5f);
    // init lookat
    cameraPos = vec3(0.0f, 0.0f, 3.0f);
    cameraFront = vec3(0.0f, 0.0f, -1.0f);
    cameraUp = vec3(0.0f, 1.0f,  0.0f);
    //
    firstMouse = true;
    yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    pitch =  0.0f;
    //lastX =  800.0f / 2.0;
    //lastY =  600.0 / 2.0;
    fov   =  45.0f;
    // texture
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
    return true;
}

void FPSTest::RenderSceneCB() {
    triangleShader->Enable();
    Transform view(libmath::genLookAtMatrix(cameraPos, cameraPos + cameraFront, cameraUp));
    triangleShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(fov), (float) 800 / 600, 1.0f, 100.0f));
    triangleShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    glBindVertexArray(VAO);
    for(unsigned int i = 0; i < 10; i++) {
        Transform model;
        float angle = 20.0f * i;
        model = model
                .translate(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z)
                .rotate(libmath::toRadians(angle), 1.0f, 1.0f, 1.0f);
        triangleShader->setUniformMatrix4fv("model", model.getTransformResult());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void FPSTest::ProcessInput(KEY_PRESS isKeyPress, float deltatime) {
    float cameraSpeed = 2.5f * deltatime; // adjust accordingly
    if(isKeyPress(GLFW_KEY_W)) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if(isKeyPress(GLFW_KEY_S)) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if(isKeyPress(GLFW_KEY_A)) {
        cameraPos -= libmath::normalize(libmath::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if(isKeyPress(GLFW_KEY_D)) {
        cameraPos += libmath::normalize(libmath::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

void FPSTest::PorcessMouseInput(float deltatime, double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    vec3 front;
    front.x = cos(libmath::toRadians(yaw)) * cos(libmath::toRadians(pitch));
    front.y = sin(libmath::toRadians(pitch));
    front.z = sin(libmath::toRadians(yaw)) * cos(libmath::toRadians(pitch));
    cameraFront = libmath::normalize(front);
}
void FPSTest::PorcessScrollInput(float deltatime, double xoffset, double yoffset) {
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 45.0f)
        fov = 45.0f;
}

//**************************************************

FPS2Test::FPS2Test() : camera(vec3(0.0f, 0.0f, 0.3f)) {
    triangleShader = NULL;
}

FPS2Test::~FPS2Test() {
    delete triangleShader;
    delete texture1;
    delete texture2;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

bool FPS2Test::Init() {
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
    // world space positions of our cubes
    cubePositions[0] = vec3(0.0f,  0.0f,  0.0f);
    cubePositions[1] = vec3(2.0f,  5.0f, -15.0f);
    cubePositions[2] = vec3(-1.5f, -2.2f, -2.5f);
    cubePositions[3] = vec3(-3.8f, -2.0f, -12.3f);
    cubePositions[4] = vec3(2.4f, -0.4f, -3.5f);
    cubePositions[5] = vec3(-1.7f,  3.0f, -7.5f);
    cubePositions[6] = vec3(1.3f, -2.0f, -2.5f);
    cubePositions[7] = vec3(1.5f,  2.0f, -2.5f);
    cubePositions[8] = vec3(1.5f,  0.2f, -1.5f);
    cubePositions[9] = vec3(-1.3f,  1.0f, -1.5f);
    // texture
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
    return true;
}

void FPS2Test::RenderSceneCB() {
    triangleShader->Enable();
    Transform view(camera.GetViewMatrix());
    triangleShader->setUniformMatrix4fv("view", view.getTransformResult());
    Transform projection(libmath::genPerspective(libmath::toRadians(camera.zoom), (float) 800 / 600, 1.0f, 100.0f));
    triangleShader->setUniformMatrix4fv("projection", projection.getTransformResult());
    glBindVertexArray(VAO);
    for(unsigned int i = 0; i < 10; i++) {
        Transform model;
        float angle = 20.0f * i;
        model = model
                .translate(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z)
                .rotate(libmath::toRadians(angle), 1.0f, 1.0f, 1.0f);
        triangleShader->setUniformMatrix4fv("model", model.getTransformResult());
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
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