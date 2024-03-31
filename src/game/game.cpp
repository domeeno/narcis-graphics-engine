#include "game.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

static int escapeKeys[] = {GLFW_KEY_ESCAPE, GLFW_KEY_Q};
static float speed = 0.01f;

void processInput(GLFWwindow *window, float &xOffset, float &yOffset,
                  float &zOffset) {
  for (int key : escapeKeys) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    yOffset += speed;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    xOffset -= speed;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    yOffset -= speed;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    xOffset += speed;
  }
}

float xOffset = .0f, yOffset = .0f, zOffset = .0f;

void playGame(GLFWwindow *window, Shader *shader) {
  processInput(window, xOffset, yOffset, zOffset);

  shader->setFloat3f("offset", xOffset, yOffset, zOffset);
}
