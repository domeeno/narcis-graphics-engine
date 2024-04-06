#ifndef SHADERS_H
#define SHADERS_H

#include "../../include/glad/glad.h"
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
  unsigned int id;

  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader();

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setFloat3f(const std::string &name, float x, float y, float z) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;
  std::string readShaderFileIntoCString(const char *path);
  GLuint init_shader(const char *source, GLuint type);
  void init_program(GLuint vertexShaderId, GLuint fragmentShaderId);
  void verify_shader_compile(GLuint &shaderId);
  void verify_program_compile(GLuint &shaderId);
};
#endif
