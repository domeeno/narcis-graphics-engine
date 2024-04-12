#include "Grid.hpp"

namespace nge {
Grid::Grid(GLfloat span, GLuint columns) {
  f32 step = span / ((f32)columns / 2);
  std::cout << "span: " << step << " columns: " << columns << " step: " << step
            << std::endl;

  for (f32 y = span; y >= -span; y -= step) {
    for (f32 x = -span; x <= span; x += step) {
      // std::cout << "{" << x << ", " << y << "};\t";
      this->Points.push_back(new Point(x, y, 0.0f, 5.0f));
    }
  //    std::cout << std::endl;
  }
}

void Grid::Draw() {
  for (Point *point : this->Points) {
    point->Draw();
  }
}

} // namespace nge
