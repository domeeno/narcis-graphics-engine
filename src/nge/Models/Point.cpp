#include "Point.hpp"

#include <GL/gl.h>

namespace nge {

Point::Point(GLfloat x, GLfloat y, GLfloat z, GLfloat radius) {
  this->Coords[0] = x;
  this->Coords[1] = y;
  this->Coords[2] = z;
  this->Radius = radius;

  // Generate and bind the vertex array object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  // Set up vertex attribute pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)Coords);
  glEnableVertexAttribArray(0);

  // Unbind the vertex array object
  glBindVertexArray(0);
}

Point::~Point() {
  // Delete the vertex array object
  glDeleteVertexArrays(1, &vao);
}

void Point::Draw() {
  // Bind the vertex array object
  glBindVertexArray(vao);
  glad_glPointSize(this->Radius);
  // Draw the point
  glDrawArrays(GL_POINTS, 0, 1);
  // Unbind the vertex array object
  glBindVertexArray(0);
  glad_glPointSize(1.0f);
}
} // namespace nge
