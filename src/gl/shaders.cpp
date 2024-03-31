#include "shaders.h"
#include <iostream>
#include <ostream>

void verify_shader_compile(unsigned int &shaderId);
void verify_program_compile(unsigned int &shaderId);

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
  std::string vertexCode = readShaderFileIntoCString(vertexPath);
  std::string fragmentCode = readShaderFileIntoCString(fragmentPath);

  unsigned int vertexShader = init_shader(vertexCode.c_str());
  unsigned int fragmentShader = init_shader(fragmentCode.c_str());

  init_program(vertexShader, fragmentShader);
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

Shader::~Shader() {
  std::cout << "::deleted prog shader id: " << id << std::endl;
  glDeleteProgram(id);
}

std::string Shader::readShaderFileIntoCString(const char *filePath) {
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

unsigned int Shader::init_shader(const char *source) {
  unsigned int vertexShaderId;

  // GL_VERTEX_SHADER specifies type of shader
  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

  std::cout << "::assgined vertex shader id: " << vertexShaderId << std::endl;

  // linking shader id to the address of vertexShaderSource
  glShaderSource(vertexShaderId, 1, &source, NULL);
  glCompileShader(vertexShaderId);

  verify_shader_compile(vertexShaderId);

  return vertexShaderId;
}

void Shader::init_program(unsigned int vertexShaderId,
                          unsigned int fragShaderId) {
  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

  std::cout << "::maximum nr of vertex attributes supported: " << nrAttributes
            << std::endl;

  id = glCreateProgram();

  glAttachShader(id, vertexShaderId);
  glAttachShader(id, fragShaderId);
  glLinkProgram(id);

  verify_program_compile(id);

  glUseProgram(id);

  glDeleteShader(fragShaderId);
  glDeleteShader(vertexShaderId);

  std::cout << "::deleted vert shader id: " << vertexShaderId << std::endl;
  std::cout << "::deleted frag shader id: " << fragShaderId << std::endl;
}

void Shader::use() { glUseProgram(id); }

// I like these colors
// vec4(0.2f, 0.5f, 1.0f, 1.0f);
// vec4(1.0f, 0.5f, 0.2f, 1.0f);
// vec4(0.5f, 1.0f, 0.2f, 1.0f);

void verify_shader_compile(unsigned int &shaderId) {
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

void verify_program_compile(unsigned int &shaderId) {
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
