#ifndef RENDER_SHADER_H_
#define RENDER_SHADER_H_

#include "../../../include/glad/glad.h"
#include "../Utils/Types.hpp"
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

namespace nge {
class Shader {
public:
  Shader();
  ~Shader();

  void Vertex(const char *path);
  void Fragment(const char *path);

  GLuint Build();

  void Use();

  void SetBool(const std::string &uniform, bool value) const;
  void SetInt(const std::string &uniform, int value) const;
  void SetFloat(const std::string &uniform, float value) const;
  void SetFloat3f(const std::string &uniform, float x, float y, float z) const;
  void SetMat4(const std::string &uniform, const glm::mat4 &mat) const;

  GLuint GetUniformLocation(const char *uniform);

private:
  GLuint VertexID;
  GLuint FragmentID;
  GLuint ProgramID;

  /**
   * Loads Graphics Language Scripting Language Files .glsl into std::string
   */
  GLSL LoadShader(const char *path);

  /**
   * Compile a Loaded GLSL String
   */
  GLuint Compile(GLSL shader, GLuint type);
};
} // namespace nge

#endif // RENDER_SHADER_H_
