#include "PerspectiveRenderer.h"
#include "domain.h"
#include "renderer.h"
#include <unistd.h>
#include <vector>
int main() {
  std::vector<float> ls{0, 4, 15};
  std::vector<float> cam_position{0, 0, 0};
  Camera camera = Camera(cam_position);
  Renderer r = Renderer(160, 80, ls, camera);
  Torus t, t2;
  std::vector<float> dim_torus{6, 3};
  t.generate(dim_torus);
  t2.generate(dim_torus);
  r.add_shape(&t);
  // r.add_shape(&t2);
  t.translate(-5, 0, 15);
  // t2.translate(5, 0, 15);
  //  for(int i=0;i<25;i++){
  //      r.display();
  //      t.translate(0,0,1);
  //      Sleep(16);
  //  }
  for (int i = 0; i < 150; i++) {
    r.display();
    t.rotate_x(10 * 3.14 / 180);
    // t2.rotate_x(-10 * 3.14 / 180);
  }
}
/*
 cd folderul_proiectului
mkdir build && cd build
cmake ..          # Generează fișierele de build (Makefiles)
cmake --build .   # Compilează proiectul efectiv
  */
