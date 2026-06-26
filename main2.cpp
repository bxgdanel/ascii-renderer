#include "PerspectiveRenderer.h"
#include "domain.h"
#include "renderer.h"
#include <unistd.h>
#include <vector>
int main() {
  std::vector<float> ls{0, 0, -1};
  PerspectiveRenderer r = PerspectiveRenderer(160, 80, ls, 60);
  Torus t{6, 3};
  Cube c{30, 30, 30};
  t.generate();
  c.generate();
  r.add_shape(&c);
  c.translate(-10, 0, 75);
  for (int i = 0; i < 150; i++) {
    r.display();
    c.rotate_z(-10 * 3.14 / 180);
    c.rotate_x(-10 * 3.14 / 180);
    usleep(10000);
  }
}
/*
 cd folderul_proiectului:
mkdir build && cd build
cmake ..          # Generează fișierele de build (Makefiles)
cmake --build .   # Compilează proiectul efectiv
  */
