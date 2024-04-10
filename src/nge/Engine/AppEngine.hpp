#ifndef ENGINE_APP_ENGINE_H_
#define ENGINE_APP_ENGINE_H_

#include "../Utils/Utils.hpp"
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
  Window *GetRender() { return this->WindowManager; };

  ~AppEngine();

private:
  static AppEngine *Instance;

  Window *WindowManager;
  Render *RenderManager;
};
} // namespace nge

#endif // ENGINE_APP_ENGINE_H_
