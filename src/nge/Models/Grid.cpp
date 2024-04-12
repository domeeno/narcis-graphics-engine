#include "Grid.hpp"

namespace nge {
Grid::Grid(GLfloat span, GLuint columns, Plane plane) {
  f32 step = span / ((f32)columns / 2);
  std::cout << "span: " << step << " columns: " << columns << " step: " << step
            << std::endl;

  GLfloat pointSize = 2.0f;
  for (f32 i = span; i >= -span; i -= step) {
    for (f32 j = -span; j <= span; j += step) {
      if (plane == XZ_PLANE) {
        this->Points.push_back(new Point(j, 0.0f, i, pointSize));
      } else if (plane == XY_PLANE) {
        this->Points.push_back(new Point(j, i, 0.0f, pointSize));
      } else if (plane == YZ_PLANE) {
        this->Points.push_back(new Point(0.0f, j, i, pointSize));
      }
    }
  }
}

void Grid::Draw() {
  for (Point *point : this->Points) {
    point->Draw();
  }
}

} // namespace nge
