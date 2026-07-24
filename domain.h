#pragma once
#include <cmath>
#include <vector>
class PerspectiveRenderer;
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
  int size = 0;
  virtual void generate() = 0;
  void rotate_x(float unghi);
  void rotate_z(float unghi);
  void rotate_x_pivot(float unghi, float x, float y, float z);
  void rotate_y_pivot(float unghi, float x, float y, float z);
  void rotate_z_pivot(float unghi, float x, float y, float z);

  void snap_to_surface();
  virtual void translate(float x, float y, float z);
};
class Cube : public Surface {
  float l, w, h;

public:
  int lx, ly, lz;
  Cube() = default;
  Cube(float l_, float w_, float h_) : l(l_), w(w_), h(h_) {}
  void generate() override;
};
class Rubik : public Surface {
  Cube cubes[27];
  PerspectiveRenderer *ren;

public:
  Rubik(PerspectiveRenderer *r) : ren{r} {
    for (int i = 0; i < 27; i++)
      cubes[i] = Cube(9.5, 9.5, 9.5);
  };
  void generate() override;
  void translate(float x, float y, float z) override;
  void register_cubes(PerspectiveRenderer *r);

  void rotate_layer_x(int layer, float unghi);
  void rotate_layer_y(int layer, float unghi);
  void rotate_layer_z(int layer, float unghi);

  void temp_rot_y(float unghi);
  void R(int sens = 1);
  void U(int sens = 1);
  void L(int sens = 1);
  void D(int sens = 1);
  void F(int sens = 1);
  void B(int sens = 1);
};
