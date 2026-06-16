#include "Camera.h"
#include "domain.h"
#include "renderer.h"
#include <unistd.h>
int main() {
  float ls[3] = {0, 2, -10};
  float cam_position[3] = {0, 0, 0};
  Camera camera = Camera(cam_position);
  Renderer r = Renderer(160, 80, ls, camera);
  Torus t, t2;
  Cube c;
  c.generate(40, 4, 40);
  t.generate(6, 3);
  t2.generate(6, 3);
  r.add_shape(&t);
  r.add_shape(&t2);
  r.add_shape(&c);
  t.translate(-10, 0, 30);
  t2.translate(10, 0, 30);
  c.translate(10, -20, 30);
  for (int i = 0; i < 150; i++) {
    r.display();
    t.rotate_x(10 * 3.14 / 180);
    t2.rotate_x(-10 * 3.14 / 180);
    // c.rotate_z(10 * 3.14 / 10);
  }
}
