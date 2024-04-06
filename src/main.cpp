#include "../include/glad/glad.h"
#include "./game/game.h"
#include "./gl/shaders.h"
#include "./lib/cglfw.h"
#include "./lib/textures.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 900;
const char *WINDOW_NAME = "Hello";

int main(int argc, char **argv) {

  GLFWwindow *window = initGlfwWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
                                      3, 3, GLFW_OPENGL_CORE_PROFILE);

  auto *shader = new Shader("src/shaders/coordinate_vs.glsl",
                            "src/shaders/texture_fs.glsl");
  glEnable(GL_DEPTH_TEST);

  float vertexArr[]{
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

      -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArr), vertexArr, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Core OpenGL requires that a VAO should be used, to know what to do with
    // vertex inputs from VBO
    // tell GL to interpret vertex data as
    // |       vertex 1     ||       vertex2      ||      vertex3       |
    // |xfloat|yfloat|zfloat||xfloat|yfloat|zfloat||xfloat|yfloat|zfloat|
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

  double lastTime = glfwGetTime();
  int nbFrames = 0;

  // wireframe mode
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >=
        1.0) { // If last printf() was more than 1 sec ago
      // Calculate FPS and print
      double fps = static_cast<double>(nbFrames) / (currentTime - lastTime);
      printf("%.2f FPS\n", fps);

      // Reset frame count and timer
      nbFrames = 0;
      lastTime = currentTime;
    }

    shader->use();
    shader->setFloat3f("colorOffset", offset, offset, offset);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
                        glm::vec3(0.5f, 1.0f, 0.0f));

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(
        glm::radians(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(shader->id, "model");
    unsigned int viewLoc = glGetUniformLocation(shader->id, "view");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // note: currently we set the projection matrix each frame, but since the
    // projection matrix rarely changes it's often best practice to set it
    // outside the main loop only once.
    shader->setMat4("projection", projection);

    playGame(window, shader);
    glBindVertexArray(vaos[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    glFlush();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete shader;

  glDeleteVertexArrays(BUFFERS, vaos);
  glDeleteBuffers(BUFFERS, vbos);

  glfwTerminate();

  return 0;
}
