#include "renderer.h"
#include "domain.h"
#include <vector>
#include <windows.h>
#include "PerspectiveRenderer.h"
int main(){
    std::vector<float> ls{0,1,-1};
    PerspectiveRenderer r = PerspectiveRenderer(160,80,ls,60);
    Torus t,t2;
    std::vector<float> dim_torus{6,3};
    t.generate(dim_torus);
    t2.generate(dim_torus);
    r.add_shape(&t);
    r.add_shape(&t2);
    t.translate(-10,0,45);
    t2.translate(10,0,45);
    // for(int i=0;i<25;i++){
    //     r.display();
    //     t.translate(0,0,1);
    //     Sleep(16);
    // }
    for(int i=0;i<150;i++)
    {
        r.display();
        t.rotate_x(10*3.14/180);
        t2.rotate_x(10*3.14/180);
    }
}