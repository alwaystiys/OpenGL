#include "Common/window_backend.h"

static ICallbacks* s_pCallbacks = NULL;
static GLFWwindow* window = NULL;
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

bool GLFWBackendCreateWindow(char* pTitle, unsigned int width, unsigned int height, bool isHideCursor) {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(width, height, pTitle, NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    if(isHideCursor) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // ---------------------------------------
    // Initialize GLEW to setup the OpenGL Function pointers
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    logGLInfo();
    return true;
}

void GLFWBackendRun(ICallbacks* pCallbacks) {
    if(!pCallbacks) {
        fprintf(stderr, "%s : callbacks not specified!\n", __FUNCTION__);
        return;
    }
    s_pCallbacks = pCallbacks;
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        s_pCallbacks->RenderSceneCB();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void logGLInfo() {
    std::cout << "--------------------GL INFO--------------------------- " << std::endl;
    GLint nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}


void GLFWBackenShutDown() {
    glfwTerminate();
}

bool isKeyPress(int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    s_pCallbacks->ProcessInput(isKeyPress, deltaTime);
    if(isKeyPress(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    s_pCallbacks->PorcessMouseInput(deltaTime, xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    s_pCallbacks->PorcessScrollInput(deltaTime, xoffset, yoffset);
}