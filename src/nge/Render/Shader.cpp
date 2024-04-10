#include "Shader.hpp"

namespace nge {
Shader::Shader() {
  this->VertexID = -1;
  this->FragmentID = -1;
  this->ProgramID = -1;
}

Shader::~Shader() {
  std::cout << "::deleted prog shader id: " << ProgramID << std::endl;
  glDeleteProgram(ProgramID);
}

void Shader::Vertex(const char *path) {
  GLSL shader = LoadShader(path);
  this->VertexID = Compile(shader, GL_VERTEX_SHADER);
}

void Shader::Fragment(const char *path) {
  GLSL shader = LoadShader(path);
  this->FragmentID = Compile(shader, GL_FRAGMENT_SHADER);
}

GLuint Shader::Build() {

  if (this->VertexID == -1 || this->FragmentID == -1) {
    return -1;
  }

  // TODO create vertex class to be able to reuse
  // TODO create fragment class to be able to reuse
  this->ProgramID = glCreateProgram();

  glAttachShader(this->ProgramID, this->VertexID);
  glAttachShader(this->ProgramID, this->FragmentID);
  glLinkProgram(this->ProgramID);

  int success;
  char infoLog[512];
  glGetProgramiv(this->ProgramID, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(this->ProgramID, 512, NULL, infoLog);
    std::cerr << "ERRO::PROG::COMPILATION_FAILED: " << infoLog << std::endl;

    return -1;
  }

  glUseProgram(this->ProgramID);

  glDeleteShader(this->VertexID);
  glDeleteShader(this->FragmentID);

  return this->ProgramID;
}

GLSL Shader::LoadShader(const char *filePath) {
  GLSL shader;

  std::ifstream file;

  try {
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(filePath);

    std::stringstream stream;

    stream << file.rdbuf();

    file.close();
    shader = stream.str();

  } catch (std::ifstream::failure e) {
    std::cerr << "ERROR::SHDR::FILE_NOT_FOUND: " << filePath << std::endl;
  }

  return shader;
}

GLuint Shader::Compile(GLSL shader, GLuint type) {
  unsigned int ID;
  ID = glCreateShader(type);

  GLSLC compilableShader = shader.c_str();

  glShaderSource(ID, 1, &compilableShader, NULL);
  glCompileShader(ID);

  int success;
  char log[512];
  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(ID, 512, NULL, log);
    std::cerr << "ERRO::SHDR::COMPILATION_FAILED: " << log << std::endl;

    return -1;
  }

  return ID;
}

void Shader::Use() {
  if (this->ProgramID == -1) {
    throw std::runtime_error("Shader program is unuseable");
  }
  glUseProgram(this->ProgramID);
}

// I like these colors
// vec4(0.2f, 0.5f, 1.0f, 1.0f);
// vec4(1.0f, 0.5f, 0.2f, 1.0f);
// vec4(0.5f, 1.0f, 0.2f, 1.0f);

GLuint Shader::GetUniformLocation(const char *uniform) {
  return glGetUniformLocation(this->ProgramID, uniform);
}

/**
 *
 * Uniform glsl manipulation methods
 *
 */
void Shader::SetBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(this->ProgramID, name.c_str()), (int)value);
}
void Shader::SetInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(this->ProgramID, name.c_str()), value);
}
void Shader::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(this->ProgramID, name.c_str()), value);
}
void Shader::SetFloat3f(const std::string &name, float x, float y,
                        float z) const {
  glUniform3f(glGetUniformLocation(this->ProgramID, name.c_str()), x, y, z);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(this->ProgramID, name.c_str()), 1,
                     GL_FALSE, &mat[0][0]);
}
} // namespace nge
