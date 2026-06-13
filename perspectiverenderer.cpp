#include "PerspectiveRenderer.h"

void PerspectiveRenderer::render(){
for(int x = 0; x < W_size; x++) {
        for(int y = 0; y < H_size; y++) {
            a[x][y] = 0;
        }
    }
    //float scale  = 1.5;
    for(auto s:shapes)
        for(int i =0;i<s->size;i++)
        {
            if(s->points[i][2]<=0.1f) continue;

            float aspect_ratio_comp = W_size/H_size;
            int screen_x = s->points[i][0]*fov*aspect_ratio_comp/s->points[i][2]+ W_size/2;
            int screen_y = s->points[i][1]*fov/s->points[i][2]+ H_size/2;
            
            if(screen_x<W_size && screen_x>=0 && screen_y<H_size && screen_y >=0){
                if(s->points[i][2]<zbuf[screen_x][screen_y]){
                        zbuf[screen_x][screen_y] = s->points[i][2];
                        float brightness_value = s->normals[i][0]*light_source[0]+ s->normals[i][1]*light_source[1] + s->normals[i][2]*light_source[2];
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