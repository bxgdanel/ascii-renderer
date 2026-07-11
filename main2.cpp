#include "PerspectiveRenderer.h"
#include "domain.h"
#include "renderer.h"
#include <unistd.h>
#include <vector>
int main() {
  std::vector<float> ls{0, 1, -1};
  PerspectiveRenderer r = PerspectiveRenderer(160, 80, ls, 60);
  Rubik c{&r};
  c.generate();
  c.register_cubes(&r);
  c.translate(-10, -5, 75);
  // c.temp_rot_y(M_PI / 4);
  for (int i = 0; i < 6; i++) {
    c.R();
    c.U();
    c.R(-1);
    c.U(-1);
  }
  // for (int i = 0; i < 150; i++) {
  //  r.display();
  //   usleep(10000);
  //}
}
