#ifndef RENDER_RENDER_H_
#define RENDER_RENDER_H_

#include "../../../include/glad/glad.h"
#include "../Utils/NonCopyable.hpp"
#include "Shader.hpp"

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace nge {
class Render : private NonCopyable {
public:
  static Render *Get() { return Instance; };

  Render();
  ~Render();

private:
  static Render *Instance;
  std::unordered_map<GLuint, Shader> shaders;
};
} // namespace nge

#endif // RENDER_RENDER_H_
