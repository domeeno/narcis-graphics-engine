#include "shaders.h"
#include <iostream>
#include <ostream>

void verify_shader_compile(unsigned int &shaderId);
void verify_program_compile(unsigned int &shaderId);

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  GLuint vertex, fragment;

  // vertex shader
  std::string vertexCode = readShaderFileIntoCString(vertexPath);
  const char *vShaderCode = vertexCode.c_str();
  vertex = init_shader(vShaderCode, GL_VERTEX_SHADER);

  // fragment shader
  std::string fragmentCode = readShaderFileIntoCString(fragmentPath);
  const char *fShaderCode = fragmentCode.c_str();
  fragment = init_shader(fShaderCode, GL_FRAGMENT_SHADER);

  init_program(vertex, fragment);
}

void Shader::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat3f(const std::string &name, float x, float y, float z) const {
  glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}


Shader::~Shader() {
  std::cout << "::deleted prog shader id: " << id << std::endl;
  glDeleteProgram(id);
}

std::string Shader::readShaderFileIntoCString(const char *filePath) {
  std::cout << "::loading shader path: " << filePath << std::endl;
  std::string shaderCodeStr;

  std::ifstream shaderFile;

  shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    shaderFile.open(filePath);

    std::stringstream shaderFStream;

    shaderFStream << shaderFile.rdbuf();

    shaderFile.close();

    shaderCodeStr = shaderFStream.str();

  } catch (std::ifstream::failure e) {
    std::cerr << "ERROR::SHDR::FILE_NOT_FOUND: " << filePath << std::endl;
  }

  return shaderCodeStr;
}

GLuint Shader::init_shader(const char *source, GLuint type) {
  unsigned int shaderId;
  shaderId = glCreateShader(type);
  glShaderSource(shaderId, 1, &source, NULL);
  glCompileShader(shaderId);
  verify_shader_compile(shaderId);
  return shaderId;
}

void Shader::init_program(unsigned int vertexShaderId,
                          unsigned int fragShaderId) {
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

  std::cout << "::maximum nr of vertex attributes supported: " << nrAttributes
            << std::endl;

  id = glCreateProgram();

  std::cout << "::attach vert shader: " << vertexShaderId << " to program "
            << id << std::endl;
  glAttachShader(id, vertexShaderId);

  std::cout << "::attach frag shader: " << fragShaderId << " to program " << id
            << std::endl;
  glAttachShader(id, fragShaderId);

  glLinkProgram(id);
  verify_program_compile(id);
  glUseProgram(id);

  glDeleteShader(vertexShaderId);
  std::cout << "::deleted vert shader id: " << vertexShaderId << std::endl;

  glDeleteShader(fragShaderId);
  std::cout << "::deleted frag shader id: " << fragShaderId << std::endl;
}

void Shader::use() { glUseProgram(id); }

// I like these colors
// vec4(0.2f, 0.5f, 1.0f, 1.0f);
// vec4(1.0f, 0.5f, 0.2f, 1.0f);
// vec4(0.5f, 1.0f, 0.2f, 1.0f);

void Shader::verify_shader_compile(unsigned int &shaderId) {
  int success;
  char infoLog[512];
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shaderId, 512, NULL, infoLog);

    std::cout << "ERRO::SHDR::COMPILATION_FAILED: " << infoLog << std::endl;
  } else {
    std::cout << "INFO::SHDR::COMPILATION_SUCCES: " << shaderId << std::endl;
  }
}

void Shader::verify_program_compile(unsigned int &shaderId) {
  int success;
  char infoLog[512];
  glGetProgramiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderId, 512, NULL, infoLog);

    std::cout << "ERRO::PROG::COMPILATION_FAILED: " << infoLog << std::endl;
  } else {
    std::cout << "INFO::PROG::COMPILATION_SUCCES: " << shaderId << std::endl;
  }
}
