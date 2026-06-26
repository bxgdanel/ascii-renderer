#pragma once
#include <cmath>
#include <vector>
using std::vector;
class Color {
public:
  int r, g, b;

public:
  Color(int red, int green, int blue) : r(red), g(green), b(blue) {}
  Color() {
    r = 0;
    g = 0;
    b = 0;
  }
};
class Surface {
public:
  vector<vector<float>> points, normals;
  vector<Color> colors;
  float center[3] = {0};
  int size;
  virtual void generate() = 0;
  void rotate_x(float unghi);
  void rotate_z(float unghi);
  void translate(float x, float y, float z);
};
class Torus : public Surface {
  int dim_r, dim_R;

public:
  Torus(int rm, int RM) : dim_r(rm), dim_R(RM) {}
  void generate() override;
};
class Cube : public Surface {
  int l, w, h;

public:
  Cube(int l_, int w_, int h_) : l(l_), w(w_), h(h_) {}
  void generate() override;
};
