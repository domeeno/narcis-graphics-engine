#include "../include/glad/glad.h"
#include "./game/game.h"
#include "./gl/shaders.h"
#include "./lib/cglfw.h"
#include "./lib/textures.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>

int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 900;
const char *WINDOW_NAME = "Hello";

int main(int argc, char **argv) {

  GLFWwindow *window = initGlfwWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
                                      3, 3, GLFW_OPENGL_CORE_PROFILE);

  auto *shader = new Shader("src/gl/vertex.glsl", "src/gl/fragment.glsl");

  float vertexArr[3][18] = //
      {{
          // positions          //color
          -0.1f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
          0.1f, -0.2f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
          0.0f, 0.15f, 0.0f, 0.0f, 0.0f, 1.0f,  // top
      }};

  unsigned char *data = load_texture_data("static/image.png");
  free_texture_data(data);

  // create a memory on the gpu where vertex data will be stored
  int BUFFERS = 1;
  unsigned int vbos[BUFFERS], vaos[BUFFERS];
  glGenBuffers(BUFFERS, vbos);
  glGenVertexArrays(BUFFERS, vaos);

  for (int i = 0; i < BUFFERS; i++) {
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // unbind reset, good practice, so no accidents or setup performed
    // uninentionally on a different buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  float offset = 0.4f;

  // wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    shader->setFloat3f("colorOffset", offset, offset, offset);

    playGame(window, shader);

    glBindVertexArray(vaos[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete shader;

  glDeleteVertexArrays(BUFFERS, vaos);
  glDeleteBuffers(BUFFERS, vbos);

  glfwTerminate();

  return 0;
}
