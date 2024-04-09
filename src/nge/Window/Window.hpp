#ifndef ENGINE_WINDOW_H_
#define ENGINE_WINDOW_H_

#include "../../../include/glad/glad.h"
#include "../Utils/Utils.hpp"
#include "KeyMap.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>

namespace nge {

class Window : NoCopy {
public:
  static Window *Get() { return Instance; };
  Window();
  ~Window();

  /**
   * Sets the window title
   */
  void SetTitle(const char *title);


  /**
   * Sets the window title
   */
  void SetFulscreen(u8 fullscreen) {
    if(!fullscreen) {
      this->GlfwMonitor = NULL;
    } else {
      this->GlfwMonitor = glfwGetPrimaryMonitor();
    }
  }

  u16 GetWidth() { return Width; };
  u16 GetHeight() { return Height; };

  void SetWidth(u16 width) { this->Width = width; };
  void SetHeight(u16 height) { this->Height = height; };
  /**
   * For GLFW Window manager setup in accordance with OpenGL version (major)
   */
  void SetMajor(u8 version);

  /**
   * For GLFW Window manager setup in accordance with OpenGL version (minor)
   */
  void SetMinor(u8 version);

  /**
   * Sets up everything for a glfwWindow
   */
  void Init();

  /**
   * Returns a GLFW window instance
   */
  GLFWwindow *GetWindow() { return this->GlfwWindow; };

  /**
   * Register a key and a function to be executed when this key was pressed
   */
  void RegisterKey(nge::KEYMAP key, std::function<void()> event);

  /**
   * Process Key Press events;
   */
  void ProcessInput();

private:
  static Window *Instance;
  GLFWwindow *GlfwWindow;
  GLFWmonitor *GlfwMonitor;
  const char *Title;
  u16 Width, Height;
  u8 Minor, Major;
  std::unordered_map<nge::KEYMAP, std::function<void()>> KeyEventMap;
};

} // namespace nge

#endif // ENGINE_WINDOW_H_
