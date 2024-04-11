#ifndef MODELS_POINT_H_
#define MODELS_POINT_H_

#include "../../../include/glad/glad.h"
#include "../Utils/Types.hpp"
#include "Model.hpp"


namespace nge {
class Point : public Model {
public:
  Point(GLfloat x, GLfloat y);
  void Draw() override;
  ~Point();

private:
  float Coords[2];
  GLuint vao;
};
} // namespace nge

#endif // MODELS_POINT_H_
