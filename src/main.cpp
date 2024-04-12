#include "../include/glad/glad.h"
#include "./lib/textures.h"
#include "nge/Engine/AppEngine.hpp"
#include "nge/Models/Grid.hpp"
#include "nge/Models/Point.hpp"
#include "nge/Render/Shader.hpp"
#include "nge/Utils/Types.hpp"
#include "nge/Window/KeyMap.hpp"
#include "nge/Window/Window.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char **argv) {
  nge::AppEngine *nge = new nge::AppEngine();
  nge::Window *window = nge->GetWindow();
  window->SetTitle("Cube");
  window->Init();

  auto *shader = new nge::Shader();
  shader->Vertex("src/shaders/vertex.glsl");
  shader->Fragment("src/shaders/fragment.glsl");
  shader->Build();

  glEnable(GL_DEPTH_TEST);

  window->RegisterKey(nge::KEYMAP::_SPACE,
                      []() -> void { std::cout << "SPACE" << std::endl; });
  window->RegisterKey(nge::KEYMAP::_Q, [window]() -> void {
    glfwSetWindowShouldClose(window->GetWindow(), true);
    std::cout << "Quitting" << std::endl;
  });

  // nge->ViewPoints();

  glm::mat4 translate = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(45.0f),
                                (float)window->GetWidth() / window->GetHeight(),
                                0.1f, 100.0f);

  translate = glm::translate(translate, glm::vec3(0.0f, 0.0f, -3.0f));

  unsigned int translateLoc = shader->GetUniformLocation("translate");
  glUniformMatrix4fv(translateLoc, 1, GL_FALSE, &translate[0][0]);
  shader->SetMat4("projection", projection);

  nge::Grid *g = new nge::Grid(16.0f, 64, nge::XZ_PLANE);

  while (!glfwWindowShouldClose(window->GetWindow())) {
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window->ProcessInput();
    shader->Use();

    g->Draw();

    glFlush();
    glfwSwapBuffers(window->GetWindow());
    glfwPollEvents();
  }

  delete shader;
  delete window;
  delete nge;

  glfwTerminate();

  return 0;
}
