#include "../include/glad/glad.h"
#include "./lib/textures.h"
#include "nge/Engine/AppEngine.hpp"
#include "nge/Models/Point.hpp"
#include "nge/Render/Shader.hpp"
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

#define DEBUG

int main(int argc, char **argv) {
  nge::AppEngine *nge = new nge::AppEngine();
  nge::Window *window = nge->GetWindow();
  window->SetTitle("Cube");
  window->Init();

  glEnable(GL_DEPTH_TEST);

  auto *shader = new nge::Shader();
  shader->Vertex("src/shaders/vertex.glsl");
  shader->Fragment("src/shaders/fragment.glsl");
  shader->Build();

  window->RegisterKey(nge::KEYMAP::_SPACE,
                      []() -> void { std::cout << "SPACE" << std::endl; });
  window->RegisterKey(nge::KEYMAP::_Q, [window]() -> void {
    glfwSetWindowShouldClose(window->GetWindow(), true);
    std::cout << "Quitting" << std::endl;
  });

  // wireframe mode

  nge->ViewPoints();

  nge::Point *p = new nge::Point(0, 0);

  while (!glfwWindowShouldClose(window->GetWindow())) {
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window->ProcessInput();

    shader->Use();
    p->Draw();

    // draw
    glFlush();
    glfwSwapBuffers(window->GetWindow());
    glfwPollEvents();
  }

  delete shader;
  delete window;

  glfwTerminate();

  return 0;
}
