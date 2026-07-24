#include "PerspectiveRenderer.h"

void PerspectiveRenderer::render() {
  ResetDepthBuffer();
  for (int x = 0; x < W_size; x++) {
    for (int y = 0; y < H_size; y++) {
      a[x][y] = 0;
    }
  }
  // float scale  = 1.5;
  float cy = cos(camera_rot_y);
  float sy = sin(camera_rot_y);
  for (auto s : shapes)
    for (int i = 0; i < s->size; i++) {
      float px = s->points[i][0] - camera_pivot[0];
      float pz = s->points[i][2] - camera_pivot[2];

      float rot_x = px * cy + pz * sy;
      float rot_z = -px * sy + pz * cy;

      rot_x += camera_pivot[0];
      rot_z += camera_pivot[2];

      if (rot_z <= 0.1f)
        continue;

      float font_aspect_ratio = 2.0f;
      int screen_x =
          (rot_x * fov * font_aspect_ratio) / rot_z + (float)W_size / 2;
      int screen_y = (s->points[i][1] * fov * font_aspect_ratio) / rot_z +
                     (float)H_size / 2;

      if (screen_x < W_size && screen_x >= 0 && screen_y < H_size &&
          screen_y >= 0) {
        if (rot_z < zbuf[screen_x][screen_y]) {
          zbuf[screen_x][screen_y] = rot_z;
          float nx = s->normals[i][0] * cy + s->normals[i][2] * sy;
          float nz = s->normals[i][0] * sy + s->normals[i][2] * cy;
          float brightness_value = nx * light_source[0] +
                                   s->normals[i][1] * light_source[1] +
                                   nz * light_source[2];
          brightness_value = brightness_value > 0 ? brightness_value : 0.50f;
          a[screen_x][screen_y] = brightness_value * (printvals_len - 1);
          color_mat[screen_x][screen_y] = s->colors[i];
        }
      }
    }
}
void PerspectiveRenderer::ResetDepthBuffer() {
  for (int x = 0; x < W_size; x++)
    for (int y = 0; y < H_size; y++)
      zbuf[x][y] = 1e19;
}
void PerspectiveRenderer::print_buffer() {
  for (int y = H_size - 1; y >= 0; y--, printf("\n"))
    for (int x = 0; x < W_size - 1; x++, printf(" ")) {
      printf("\033[38;2;%d;%d;%dm%c\033[0m", color_mat[x][y].r,
             color_mat[x][y].g, color_mat[x][y].b, printvals[a[x][y]]);
    }
}
PerspectiveRenderer::PerspectiveRenderer(int w, int h, vector<float> ls,
                                         int _fov) {
  W_size = w;
  H_size = h;
  light_source = ls;
  fov = _fov;
  a.resize(W_size, vector<int>(H_size, 0));
  zbuf.resize(W_size, vector<float>(H_size, 0.0f));
  color_mat.resize(W_size, vector<Color>(H_size, Color()));
  float we = sqrt(pow(light_source[0], 2) + pow(light_source[1], 2) +
                  pow(light_source[2], 2));
  light_source[0] = light_source[0] / we;
  light_source[1] = light_source[1] / we;
  light_source[2] = light_source[2] / we;
}
