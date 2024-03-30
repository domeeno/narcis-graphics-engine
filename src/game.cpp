#include "../include/glad/glad.h"
#include "game.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

static int escapeKeys[] = {GLFW_KEY_ESCAPE, GLFW_KEY_Q};

void processInput(GLFWwindow *window) {
  for (int key : escapeKeys) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
  }
}

float vertices[] = {
    -0.5f, -0.5f, 0.0f, //
    0.5f,  -0.5f, 0.0f, //
    0.0f,  0.5f,  0.0f  //
};

void playGame(GLFWwindow *window) {
  processInput(window);
  glClearColor(0.2f, 0.2f, 0.2f, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}
