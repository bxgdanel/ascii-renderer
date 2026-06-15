#pragma once
#include <vector>
using std::vector;
struct Ray {
  std::vector<float> origin;
  std::vector<float> direction;
};
class Camera {
public:
  std::vector<float> Coords;
  Ray get_ray(int x, int y, int W_size, int H_size);
  Camera(vector<float> c) : Coords{c} {}
  Camera() {}
};
