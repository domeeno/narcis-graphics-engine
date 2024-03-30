#include "../include/glad/glad.h"
#include "cglfw.h"
#include "game.h"
#include "shaders.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>

int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 900;
const char *WINDOW_NAME = "Hello";

int main(int argc, char **argv) {

  GLFWwindow *window = initGlfwWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
                                      3, 3, GLFW_OPENGL_CORE_PROFILE);

  int vertexShaderId = init_vertex_shader();

  unsigned int shaderProgramBlue = init_shader_program(
      vertexShaderId,
      init_fragment_shader() // return fragment shader program id
  );

  unsigned int shaderProgramGreen = init_shader_program(
      vertexShaderId,
      init_fragment_green() // return fragment shader program id
  );

  glDeleteShader(vertexShaderId);

  float vertexArr[3][9] = //
      {{
           -0.4f, -0.2f, 0.0f, // bottom left
           -0.2f, -0.2f, 0.0f, // bottom right
           -0.3f, 0.15f, 0.0f, // top
       },
       {
           -0.1f, -0.2f, 0.0f, // bottom left
           0.1f, -0.2f, 0.0f,  // bottom right
           0.0f, 0.15f, 0.0f,  // top
       },
       {
           0.2f, -0.2f, 0.0f, // bottom left
           0.4f, -0.2f, 0.0f, // bottom right
           0.3f, 0.15f, 0.0f  // top
       }};

  // create a memory on the gpu where vertex data will be stored
  unsigned int vbos[3], vaos[3];
  glGenBuffers(3, vbos);
  glGenVertexArrays(3, vaos);

  for (int i = 0; i < 3; i++) {
    // vertex buffer array object binding
    glBindVertexArray(vaos[i]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArr[i]), vertexArr[i],
                 GL_STATIC_DRAW);

    // Core OpenGL requires that a VAO should be used, to know what to do with
    // vertex inputs from VBO
    // tell GL to interpret vertex data as
    // |       vertex 1     ||       vertex2      ||      vertex3       |
    // |xfloat|yfloat|zfloat||xfloat|yfloat|zfloat||xfloat|yfloat|zfloat|
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // unbind reset, good practice, so no accidents or setup performed
    // uninentionally on a different buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  // wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    playGame(window);

    float timeValue = glfwGetTime();
    float blueValue = (sin(timeValue) / 2.0f) + 0.5f;

    int vertexColorLocation =
        glGetUniformLocation(shaderProgramBlue, "sinColor");
    glUseProgram(shaderProgramBlue);

    glUniform4f(vertexColorLocation, 0.2f, 0.5f, blueValue, 1.0f);

    glBindVertexArray(vaos[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgramGreen);

    glBindVertexArray(vaos[2]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(2, vaos);
  glDeleteBuffers(2, vbos);

  glDeleteProgram(shaderProgramBlue);
  glDeleteProgram(shaderProgramGreen);

  glfwTerminate();

  return 0;
}
