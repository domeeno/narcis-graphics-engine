#ifndef ENGINE_WINDOW_H_
#define ENGINE_WINDOW_H_

#include "../../../include/glad/glad.h"
#include "../Utils/Utils.hpp"
#include <GLFW/glfw3.h>

namespace nge {

class Window : NoCopy {
public:
  static Window *Get() { return Instance; };
  Window(u16 width, u16 height);
  ~Window();

  /**
   * Sets the window title
   */
  void SetTitle(const char *title);

  /**
   * For GLFW Window manager setup in accordance with OpenGL version (major)
   */
  void SetMajor(u8 version);

  /**
   * For GLFW Window manager setup in accordance with OpenGL version (minor)
   */
  void SetMinor(u8 version);

  /**
   * sets up everything for a glfwWindow
   */
  void Init();

  GLFWwindow *GetWindow() { return this->GlfwWindow; };

  void RegisterKey();
  void ProcessInput();

private :
  static Window *Instance;
  GLFWwindow *GlfwWindow;
  const char *Title;
  u16 Width, Height;
  u8 Minor, Major;
};

} // namespace nge

#endif // ENGINE_WINDOW_H_
