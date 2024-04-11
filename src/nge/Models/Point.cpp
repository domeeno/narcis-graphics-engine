#include "Point.hpp"

#include <GL/gl.h>

namespace nge {

Point::Point(GLfloat x, GLfloat y) {
  this->Coords[0] = x;
  this->Coords[1] = y;

  // Generate and bind the vertex array object
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  // Set up vertex attribute pointers
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
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
  glEnable(GL_BLEND);
  glad_glPointSize(20.0f);
  // Draw the point
  glDrawArrays(GL_POINTS, 0, 1);
  // Unbind the vertex array object
  glBindVertexArray(0);
  glad_glPointSize(1.0f);

}
} // namespace nge
