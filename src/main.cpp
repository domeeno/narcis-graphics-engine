#include "../include/glad/glad.h"
#include "game.h"
#include "shaders.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdlib>


int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 900;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main(int argc, char **argv) {
  GLFWwindow *window;

  if (!glfwInit())
    return EXIT_FAILURE;

  // for glfw to know more about the context and adjust its functionality
  // accordingly
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // access to a smaller subset of OpenGL features without backwards-compatible
  // features
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);

  if (!window) {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // init GLAD to manage function pointers to OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  unsigned int vertexShader = init_vertex_shader();
  unsigned int fragmentShader = init_fragment_shader();

  init_shader_program(vertexShader, fragmentShader);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    processInput(window);

    // rendering
    playGame();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
