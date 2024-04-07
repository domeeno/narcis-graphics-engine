#include "Window.hpp"
#include "KeyMap.hpp"

/**
 * callback function triggered by window resizing
 */
static void framebuffer_size_callback(GLFWwindow *window, int width,
                                      int height) {
  glViewport(0, 0, width, height);
}

namespace nge {
Window *Window::Instance = nullptr;

Window::Window(u16 width, u16 height) {
  this->Width = width;
  this->Height = height;
  this->Major = 3;
  this->Minor = 3;
  this->Title = "NarcisGE";
}

Window::~Window() {}

/**
 * Sets the window title
 */
void Window::SetTitle(const char *title) { this->Title = title; }

/**
 * For GLFW Window manager setup in accordance with OpenGL version (major)
 */
void Window::SetMajor(u8 version) { this->Major = version; }

/**
 * For GLFW Window manager setup in accordance with OpenGL version (minor)
 */
void Window::SetMinor(u8 version) { this->Minor = version; }

void Window::RegisterKey(nge::KEYMAP key, std::function<void()> event) {
  this->KeyEventMap[key] = event;
}

void Window::ProcessInput() {

  for (auto &it : this->KeyEventMap) {
    if (glfwGetKey(this->GlfwWindow, static_cast<int>(it.first)) ==
        GLFW_PRESS) {
      it.second();
    }
  }
}

/**
 * sets up everything for a glfwWindow
 */
void Window::Init() {
  if (!glfwInit()) {
    return;
  }

  /**
   * for glfw to know more about the context and adjust its functionality
   * accordingly
   */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->Major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->Minor);

  /**
   * access to a smaller subset of OpenGL features without backwards-compatible
   * features
   */
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->GlfwWindow =
      glfwCreateWindow(this->Width, this->Height, this->Title, NULL, NULL);

  if (!this->GlfwWindow) {
    glfwTerminate();
    return;
  }

  glfwMakeContextCurrent(this->GlfwWindow);
  glfwSetFramebufferSizeCallback(this->GlfwWindow, framebuffer_size_callback);
  // init GLAD to manage function pointers to OpenGL
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
  }
}
} // namespace nge
