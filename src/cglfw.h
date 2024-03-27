#ifndef CGLFW_H
#define CGLFW_H

#include <GLFW/glfw3.h>

GLFWwindow *initGlfwWindow(int windowWidth, int windowHeight, const char *windowName,
                           int glfwVersionMajor, int glfwVersionMinor,
                           int glProfile);

#endif // CGLFW_H
