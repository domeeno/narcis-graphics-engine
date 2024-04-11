#ifndef ENGINE_APP_ENGINE_H_
#define ENGINE_APP_ENGINE_H_

#include "../Utils/Utils.hpp"
#include "../../../include/glad/glad.h"
#include "../Window/Window.hpp"
#include "../Render/Render.hpp"

namespace nge {

/**
 * AppEngine - application lifecycle manager
 */
class AppEngine : private NonCopyable {

public:
  static AppEngine *Get() { return Instance; }
  explicit AppEngine();

  Window *GetWindow() { return this->WindowManager; };

  void ViewWireframe() { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);};
  void ViewPoints() { glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);};
  void ViewNormal() { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);};

  ~AppEngine();

private:
  static AppEngine *Instance;

  Window *WindowManager;
  Render *RenderManager;
};
} // namespace nge

#endif // ENGINE_APP_ENGINE_H_
