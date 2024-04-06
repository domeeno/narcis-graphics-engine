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

  auto *shader =
      new Shader("src/shaders/texture_vs.glsl", "src/shaders/texture_fs.glsl");

  float vertexArr[3][32] = //
      {{
          // positions          //color
          0.1f,  0.2f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top right
          0.1f,  -0.2f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // bottom right
          -0.1f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom left
          -0.1f, 0.2f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // top left
      }};

  unsigned int indices[] = {
      0, 1, 3, // first triang
      1, 2, 3, // second triang
  };

  // create a memory on the gpu where vertex data will be stored
  int BUFFERS = 1;
  unsigned int vbos[BUFFERS], vaos[BUFFERS], ebos[BUFFERS];
  glGenBuffers(BUFFERS, vbos);
  glGenBuffers(BUFFERS, ebos);
  glGenVertexArrays(BUFFERS, vaos);

  for (int i = 0; i < BUFFERS; i++) {
    // vertex buffer array object binding
    glBindVertexArray(vaos[i]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArr[i]), vertexArr[i],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Core OpenGL requires that a VAO should be used, to know what to do with
    // vertex inputs from VBO
    // tell GL to interpret vertex data as
    // |       vertex 1     ||       vertex2      ||      vertex3       |
    // |xfloat|yfloat|zfloat||xfloat|yfloat|zfloat||xfloat|yfloat|zfloat|
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    // colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // unbind reset, good practice, so no accidents or setup performed
    // uninentionally on a different buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  unsigned int textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D,
                textureId); // all upcoming GL_TEXTURE_2D operations now have
                            // effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(
      GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
      GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  Texture *texture = new Texture("static/image.png");

  if (texture->data != NULL) {

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texture->data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }

  delete texture;

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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
