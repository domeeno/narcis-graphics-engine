#include "shaders.h"
#include "../include/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *defaultVertexShaderSource = R"glsl(
  #version 330 core
  layout (location = 0) in vec3 aPos;
  layout (location = 1) in vec3 aColor;

  out vec3 ourColor;

  void main() {
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
  }
)glsl";

// I like this color vec4(0.2f, 0.5f, 1.0f, 1.0f);

const char *fragmentShaderBlue = R"glsl(
  #version 330 core
  out vec4 FragColor;
  in vec3 ourColor;

  void main() {
    FragColor = vec4(ourColor, 1.0f);
  }
)glsl";

const char *fragmentShaderOrange = R"glsl(
  #version 330 core
  out vec4 FragColor;
  void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  }
)glsl";

const char *fragmentShaderGreen = R"glsl(
  #version 330 core
  out vec4 FragColor;
  void main() {
    FragColor = vec4(0.5f, 1.0f, 0.2f, 1.0f);
  }
)glsl";

static void verify_shader_compile(unsigned int &shaderId);
static void verify_program_compile(unsigned int &shaderId);

unsigned int init_vertex_shader() {

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

  std::cout << "::maximum nr of vertex attributes supported: " << nrAttributes
            << std::endl;

  unsigned int vertexShaderId;

  // GL_VERTEX_SHADER specifies type of shader
  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

  std::cout << "::assgined vertex shader id: " << vertexShaderId << std::endl;

  // linking shader id to the address of vertexShaderSource
  glShaderSource(vertexShaderId, 1, &defaultVertexShaderSource, NULL);
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
  glShaderSource(fragmentShaderId, 1, &fragmentShaderBlue, NULL);
  glCompileShader(fragmentShaderId);

  verify_shader_compile(fragmentShaderId);

  return fragmentShaderId;
}

unsigned int init_shader_program(unsigned int vertexShaderId,
                                 unsigned int fragmentShaderId) {
  unsigned int shaderProgramId;
  shaderProgramId = glCreateProgram();

  glAttachShader(shaderProgramId, vertexShaderId);
  glAttachShader(shaderProgramId, fragmentShaderId);
  glLinkProgram(shaderProgramId);

  verify_program_compile(shaderProgramId);

  glUseProgram(shaderProgramId);

  glDeleteShader(fragmentShaderId);

  std::cout << "::deleted fragment shader id: " << fragmentShaderId
            << std::endl;

  return shaderProgramId;
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
