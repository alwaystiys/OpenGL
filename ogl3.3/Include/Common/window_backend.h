#ifndef WINDOW_BACKEND_H
#define WINDOW_BACKEND_H

#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include "Common/app_callbacks.h"

bool GLFWBackendCreateWindow(char* pTitle, unsigned int width, unsigned int height, bool isHideCursor = false);
void GLFWBackendRun(ICallbacks* pCallbacks);
void GLFWBackenShutDown();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

void logGLInfo();




#endif WINDOW_BACKEND_H