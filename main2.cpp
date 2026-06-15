#include "domain.h"
#include "renderer.h"
#include "Camera.h"
#include <unistd.h>
#include <vector>
int main() {
  float ls[3] = {0, 2, -10};
  float cam_position[3] ={0, 0, 0};
  Camera camera = Camera(cam_position);
  Renderer r = Renderer(160, 80, ls, camera);
  Torus t, t2;
  t.generate(6,3);
  t2.generate(6,3);
  r.add_shape(&t);
  r.add_shape(&t2);
  t.translate(-10, 0, 30);
  t2.translate(10,0,30);
  for (int i = 0; i < 150; i++) {
    r.display();
    t.rotate_x(10 * 3.14 / 180);
    t2.rotate_x(-10 * 3.14 / 180);
  }
}
