#include "renderer.h"
#include "Camera.h"
#include "domain.h"
#include <stdio.h>
#include <unistd.h>

Renderer::Renderer(int w, int h, vector<float> ls, Camera camera) {
  W_size = w;
  H_size = h;
  light_source = ls;
  a.resize(W_size, vector<int>(H_size, 0));
  zbuf.resize(W_size, vector<float>(H_size, 0.0f));

  float we = sqrt(pow(light_source[0], 2) + pow(light_source[1], 2) +
                  pow(light_source[2], 2));
  light_source[0] = light_source[0] / we;
  light_source[1] = light_source[1] / we;
  light_source[2] = light_source[2] / we;
  this->camera = camera;
}
void Renderer::print_buffer() {
  for (int y = H_size - 1; y >= 0; y--, printf("\n"))
    for (int x = 0; x < W_size - 1; x++, printf(" ")) {
      printf("%c", printvals[a[x][y]]);
    }
}
void Renderer::ResetDepthBuffer() {
  for (int x = 0; x < W_size; x++)
    for (int y = 0; y < H_size; y++)
      zbuf[x][y] = -1e19;
}
void Renderer::setCursorPosition(int x, int y) {
  printf("\033[%d;%dH", y + 1, x + 1);
  fflush(stdout);
}
void Renderer::render() {
  for (int y = 0; y < H_size; y++)
    for (int x = 0; x < W_size; x++) {
      Ray ray = camera.get_ray(x, y, W_size, H_size);

      float t_min = 1e9;
      const Surface *closest_surf = nullptr;
      vector<float> intersection_norm;

      for (auto s : shapes) {
        float t = 1e9f;
        vector<float> normal;
        if (s->intersect(ray, t, normal))
          if (t < t_min && t > 0) {
            t_min = t;
            closest_surf = s;
            intersection_norm = normal;
          }
      }
      if (closest_surf != nullptr) {
        float n_len = sqrt(intersection_norm[0] * intersection_norm[0] +
                           intersection_norm[1] * intersection_norm[1] +
                           intersection_norm[2] * intersection_norm[2]);
        if (n_len > 0) {
          intersection_norm[0] /= n_len;
          intersection_norm[1] /= n_len;
          intersection_norm[2] /= n_len;
        }
        float brightness = intersection_norm[0] * light_source[0] +
                           intersection_norm[1] * light_source[1] +
                           intersection_norm[2] * light_source[2];

        float ambient = 0.15f;
        brightness = brightness > 0 ? (brightness + ambient) : 0;
        if (brightness > 1.0f)
          brightness = 1.0f;
        a[x][y] = brightness * (printvals_len - 1);
      } else {
        a[x][y] = 0;
      }
    }
}

void Renderer::display() {
  setCursorPosition(0, 0);
  ResetDepthBuffer();
  render();
  print_buffer();
}
void Renderer::add_shape(const Surface *s) { shapes.push_back(s); }
