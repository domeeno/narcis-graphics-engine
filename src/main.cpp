#include "../include/glad/glad.h"
#include "cglfw.h"
#include "game.h"
#include "shaders.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 900;
const char *WINDOW_NAME = "Hello";

int main(int argc, char **argv) {

  GLFWwindow *window = initGlfwWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
                                     3, 3, GLFW_OPENGL_CORE_PROFILE);


  unsigned int shaderProgram = init_shader_program(
      init_vertex_shader(),  // return vertex shader program id
      init_fragment_shader() // return fragment shader program id
  );

  float vertices[] = {
      -0.1f, -0.2f, 0.0f, // bottom left
      0.1f,  -0.2f, 0.0f, // bottom right
      0.0f,  0.15f, 0.0f  // top
  };

  unsigned int VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // tell GL to interpret vertex data as
  // |       vertex 1     ||       vertex2      ||      vertex3       |
  // |xfloat|yfloat|zfloat||xfloat|yfloat|zfloat||xfloat|yfloat|zfloat|
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    playGame(window);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
