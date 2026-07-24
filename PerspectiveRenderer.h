#pragma once
#include "domain.h"
#include "renderer.h"
class PerspectiveRenderer : public Renderer {
  int fov;
  void render() override;
  void ResetDepthBuffer() override;
  vector<vector<Color>> color_mat;
  void print_buffer() override;

public:
  PerspectiveRenderer(int width, int height, vector<float> light_source,
                      int fov);
  float camera_rot_y = 0.0f;
  float camera_pivot[3];
};
