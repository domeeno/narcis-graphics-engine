#ifndef ENGINE_APP_ENGINE_H_
#define ENGINE_APP_ENGINE_H_

#include "../Utils/NoCopy.hpp"
#include "../Window/Window.hpp"

namespace nge {

/**
 * AppEngine - application lifecycle manager
 */
class AppEngine : NoCopy {

public:
  static AppEngine *Get() { return Instance; }
  explicit AppEngine();

  Window *GetWindow() { return this->WindowManager; };

  ~AppEngine();

private:
  static AppEngine *Instance;
  Window *WindowManager;
};
} // namespace nge

#endif // ENGINE_APP_ENGINE_H_
