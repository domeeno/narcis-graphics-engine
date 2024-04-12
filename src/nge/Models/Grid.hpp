#ifndef MODELS_GRID_H_
#define MODELS_GRID_H_

#include "../../../include/glad/glad.h"
#include "../Utils/Types.hpp"
#include "Model.hpp"
#include "Point.hpp"
#include "Point.hpp"

#include <iostream>
#include <vector>

namespace nge {
class Grid : public Model {
public:
  Grid(GLfloat span, GLuint columns);
  void Draw() override;
  ~Grid();

private:
  std::vector<Point*> Points;
  GLuint vao;
};
} // namespace nge

#endif // MODELS_GRID_H_
