#include "game.h"
#include "../include/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>


float vertices[] = {
    -0.5f, -0.5f, 0.0f, //
    0.5f,  -0.5f, 0.0f, //
    0.0f,  0.5f,  0.0f  //
};

void playGame() {
  glClearColor(0.2f, 0.2f, 0.2f, 1);
  glClear(GL_COLOR_BUFFER_BIT);
}
