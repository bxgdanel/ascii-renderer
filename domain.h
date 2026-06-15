#pragma once
#include "Camera.h"
#include <cmath>
#include <vector>
using std::vector;
class Surface {
public:
  vector<vector<float>> points, normals;
  float center[3] = {0};
  int size;
  virtual void generate(vector<float> dimensions) = 0;
  void rotate_x(float unghi);
  void rotate_z(float unghi);
  void translate(float x, float y, float z);
  bool intersect(Ray &ray, float &t, vector<float> &normals) const;
};
class Torus : public Surface {
public:
  void generate(vector<float> dimensions) override;
};
