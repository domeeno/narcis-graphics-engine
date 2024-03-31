#ifndef SHADERS_H
#define SHADERS_H

#include "../../include/glad/glad.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
private:
public:
  unsigned int id;

  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader();

  void use();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;

  // TODO make private somehow
  std::string readShaderFileIntoCString(const char *filePath);
  unsigned int init_shader(const char *source);
  void init_program(unsigned int vertexShaderId, unsigned int fragmentShaderId);
};

#endif // SHADERS_H
