#include "PerspectiveRenderer.h"

void PerspectiveRenderer::render(const Surface* surface){
for(int x = 0; x < W_size; x++) {
        for(int y = 0; y < H_size; y++) {
            a[x][y] = 0;
        }
    }
    //float scale  = 1.5;
    for(int i =0;i<surface->size;i++)
    {
        if(surface->points[i][2]<=0.1f) continue;

        float aspect_ratio_comp = W_size/H_size;
        int screen_x = surface->points[i][0]*fov*aspect_ratio_comp/surface->points[i][2]+ W_size/2;
        int screen_y = surface->points[i][1]*fov/surface->points[i][2]+ H_size/2;
        
        if(screen_x<W_size && screen_x>=0 && screen_y<H_size && screen_y >=0){
            if(surface->points[i][2]<zbuf[screen_x][screen_y]){
                    zbuf[screen_x][screen_y] = surface->points[i][2];
                    float brightness_value = surface->normals[i][0]*light_source[0]+ surface->normals[i][1]*light_source[1] + surface->normals[i][2]*light_source[2];
                    brightness_value  = brightness_value > 0?brightness_value:0;
                    a[screen_x][screen_y]=brightness_value*(printvals_len-1);
            }
        }
    }
}
void PerspectiveRenderer::ResetDepthBuffer(){
    for(int x=0;x<W_size;x++)
        for(int y=0;y<H_size;y++)
            zbuf[x][y]=1e19;
}
PerspectiveRenderer::PerspectiveRenderer(int w,int h,vector<float> ls,int _fov){
    W_size = w;
    H_size = h;
    light_source = ls;
    fov = _fov;
    a.resize(W_size, vector<int>(H_size, 0));
    zbuf.resize(W_size, vector<float>(H_size, 0.0f));

    float we = sqrt(pow(light_source[0],2)+pow(light_source[1],2)+pow(light_source[2],2));
    light_source[0] = light_source[0]/we;
    light_source[1] = light_source[1]/we;
    light_source[2] = light_source[2]/we;

}