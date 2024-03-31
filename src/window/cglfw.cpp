#include "../include/glad/glad.h"
#include "cglfw.h"
#include <cstdlib>

/**
 * callback function triggered by window resizing
 */
static void framebuffer_size_callback(GLFWwindow *window, int width,
                                      int height) {
  glViewport(0, 0, width, height);
}

/**
 * Initializes a glfw window struct with some options
 * @param wWidth - window width
 * @param wHeight - window height
 * @param wTitle - window title
 * @param glfwVMajor - OpenGL major version param
 * @param glfwVMinor - OpenGL minor version param
 * @param glProfile - OpenGL profile used (core/not core)
 */
GLFWwindow *initGlfwWindow(int wWidth, int wHeight, const char *wTitle,
                           int glfwVMajor, int glfwVMinor, int glProfile) {
  GLFWwindow *window;

  if (!glfwInit())
    exit(EXIT_FAILURE);

  /**
   * for glfw to know more about the context and adjust its functionality
   * accordingly
   */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glfwVMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glfwVMinor);

  /**
   * access to a smaller subset of OpenGL features without backwards-compatible
   * features
   */
  glfwWindowHint(GLFW_OPENGL_PROFILE, glProfile);

  window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL);

  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // init GLAD to manage function pointers to OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  return window;
}
