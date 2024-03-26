#include "shaders.h"
#include "../include/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

static void verify_shader_compile(unsigned int &shaderId);
static void verify_program_compile(unsigned int &shaderId);

unsigned int init_vertex_shader() {
  unsigned int vertexShaderId;

  // GL_VERTEX_SHADER specifies type of shader
  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

  std::cout << "::assgined vertex shader id: " << vertexShaderId << std::endl;

  // linking shader id to the address of vertexShaderSource
  glShaderSource(vertexShaderId, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShaderId);

  verify_shader_compile(vertexShaderId);

  return vertexShaderId;
}

unsigned int init_fragment_shader() {
  unsigned int fragmentShaderId;

  // GL_VERTEX_SHADER specifies type of shader
  fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

  std::cout << "::assgined fragment shader id: " << fragmentShaderId
            << std::endl;

  // linking shader id to the address of vertexShaderSource
  glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShaderId);

  verify_shader_compile(fragmentShaderId);

  return fragmentShaderId;
}

void init_shader_program(unsigned int vertexShaderId,
                         unsigned int fragmentShaderId) {
  unsigned int shaderProgramId;
  shaderProgramId = glCreateProgram();

  glAttachShader(shaderProgramId, vertexShaderId);
  glAttachShader(shaderProgramId, fragmentShaderId);
  glLinkProgram(shaderProgramId);

  verify_program_compile(shaderProgramId);
}

static void verify_shader_compile(unsigned int &shaderId) {
  int success;
  char infoLog[512];
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shaderId, 512, NULL, infoLog);

    std::cout << "ERROR::SHADER::COMPILATION_FAILED: " << infoLog << std::endl;
  }
}

static void verify_program_compile(unsigned int &shaderId) {
  int success;
  char infoLog[512];
  glGetProgramiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderId, 512, NULL, infoLog);

    std::cout << "ERROR::PROGRAM::COMPILATION_FAILED: " << infoLog << std::endl;
  }
}
