#include "Camera.h"
#include <cmath>
using std::vector;
Ray Camera::get_ray(int x, int y, int W_size, int H_size) {
  Ray ray;
  ray.origin = this->Coords;

  float aspect_ratio = ((float)W_size / (float)H_size) * 0.5;
  float normalized_x = (2.0f * (x + 0.5f) / W_size - 1.0f) * aspect_ratio;
  float normalized_y = (2.0f * (y + 0.5f) / H_size - 1.0f);

  vector<float> pos;
  pos.push_back(normalized_x);
  pos.push_back(normalized_y);
  pos.push_back(1.0f);
  float len =
      sqrt(normalized_x * normalized_x + normalized_y * normalized_y + 1.0f);
  if (len != 0) {
    pos[0] /= len;
    pos[1] /= len;
    pos[2] /= len;
  }
  ray.direction = pos;
  return ray;
}
