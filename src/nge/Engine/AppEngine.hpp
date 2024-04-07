#ifndef ENGINE_APP_ENGINE_H_
#define ENGINE_APP_ENGINE_H_

#include "../Utils/NoCopy.hpp"

#include <string>

namespace nge {

/**
 * AppEngine - application lifecycle manager
 */
class AppEngine : NoCopy {

public:
  static AppEngine *Get() { return Instance; }
  explicit AppEngine(std::string projectName);

  ~AppEngine();

private:
  static AppEngine *Instance;
};
} // namespace nge

#endif // ENGINE_APP_ENGINE_H_
