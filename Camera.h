#pragma once
#include <vector>
using std::vector;
struct Ray {
 float origin[3];
 float direction[3];
};
class Camera {
public:
  float Coords[3];
  Ray get_ray(int x, int y, int W_size, int H_size);
  Camera(float c[3]){Coords[0] = c[0], Coords[1] = c[1], Coords[2] = c[2];}
  Camera() {}
};
