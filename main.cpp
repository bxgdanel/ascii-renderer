#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <cmath>
#include <vector>
#include <stdio.h>
using namespace std;
#define W_size 80
#define H_size 40
 
int a[W_size][H_size]={0};//screen buffer
int zbuf[W_size][H_size];//depth buffer
vector<float> light_source = {0,1,1};
const char printvals[] = " .,-~:;=!*#$%@";
const int printvals_len = 14;
struct Surface{
    vector<vector<float>> points;
    vector<vector<float>> normals;
    int size;
};
void render(Surface surface){
    for(int x = 0; x < W_size; x++) {
        for(int y = 0; y < H_size; y++) {
            a[x][y] = 0;
        }
    }
    float scale  = 1.5;
    for(int i =0;i<surface.size;i++)
    {
        float aspect_ratio_comp = W_size/H_size;
        int screen_x = surface.points[i][0]*scale*aspect_ratio_comp + W_size/2;
        int screen_y = surface.points[i][1]*scale + H_size/2;
        
        if(screen_x<W_size && screen_x>=0 && screen_y<H_size && screen_y >=0){
            if(surface.points[i][2]>zbuf[screen_x][screen_y]){
                    zbuf[screen_x][screen_y] = surface.points[i][2];
                    float brightness_value = surface.normals[i][0]*light_source[0]+ surface.normals[i][1]*light_source[1] + surface.normals[i][2]*light_source[2];
                    brightness_value  = brightness_value?brightness_value:0;
                    a[screen_x][screen_y]=brightness_value*(printvals_len-1);
            }
        }
    }
}
//genereaza matricea cu punctele care apartin torusului
Surface Torus(int R,int r){
vector<vector<float>> points;
vector<vector<float>> normals;
for(float theta = 0;theta<6.28;theta+=0.03)
    for(float phi =0;phi<6.28;phi+=0.03){
        vector<float> tmp;
        vector<float> tmp_norm;
        tmp.push_back((R+r*cos(theta))*cos(phi));//x conform ec param
        tmp.push_back((R+r*cos(theta))*sin(phi));//y conform ec param
        tmp.push_back(r*sin(theta));

        tmp_norm.push_back(cos(theta)*cos(phi));
        tmp_norm.push_back(cos(theta)*sin(phi));
        tmp_norm.push_back(sin(theta));

        points.push_back(tmp);
        normals.push_back(tmp_norm);
    }
    Surface s;
    s.points = points;
    s.normals = normals;
    s.size = points.size();
    return s;
}
Surface Rot(Surface toRotate,float unghi_X,float unghi_Z){
    float RotationMatrix[3][3]={{1,0,0},{0,cos(unghi_X),-sin(unghi_X)},{0,sin(unghi_X),{cos(unghi_X)}}};
    vector<vector<float>> points;
    vector<vector<float>> normals;
    for(int i =0;i<toRotate.size;i++){
            vector<float> tmp;
            tmp.push_back(RotationMatrix[0][0]*toRotate.points[i][0] +RotationMatrix[0][1]*toRotate.points[i][1] + RotationMatrix[0][2]*toRotate.points[i][2]);
            tmp.push_back(RotationMatrix[1][0]*toRotate.points[i][0] +RotationMatrix[1][1]*toRotate.points[i][1] + RotationMatrix[1][2]*toRotate.points[i][2]);
            tmp.push_back(RotationMatrix[2][0]*toRotate.points[i][0] +RotationMatrix[2][1]*toRotate.points[i][1] + RotationMatrix[2][2]*toRotate.points[i][2]);
            points.push_back(tmp);

            vector<float> tmp_norm;
            tmp_norm.push_back(RotationMatrix[0][0]*toRotate.normals[i][0] +RotationMatrix[0][1]*toRotate.normals[i][1] + RotationMatrix[0][2]*toRotate.normals[i][2]);
            tmp_norm.push_back(RotationMatrix[1][0]*toRotate.normals[i][0] +RotationMatrix[1][1]*toRotate.normals[i][1] + RotationMatrix[1][2]*toRotate.normals[i][2]);
            tmp_norm.push_back(RotationMatrix[2][0]*toRotate.normals[i][0] +RotationMatrix[2][1]*toRotate.normals[i][1] + RotationMatrix[2][2]*toRotate.normals[i][2]);
            normals.push_back(tmp_norm);
    }
    Surface s;
    s.points = points;
    s.normals = normals;
    s.size = toRotate.size;
    return s;

}
Surface Rotz(Surface toRotate,float unghi_X,float unghi_Z){
    float RotationMatrix[3][3]={{cos(unghi_Z),-sin(unghi_Z),0},{sin(unghi_Z),cos(unghi_X),0},{0,0,1}};
    vector<vector<float>> points;
    vector<vector<float>> normals;
    for(int i =0;i<toRotate.size;i++){
            vector<float> tmp;
            tmp.push_back(RotationMatrix[0][0]*toRotate.points[i][0] +RotationMatrix[0][1]*toRotate.points[i][1] + RotationMatrix[0][2]*toRotate.points[i][2]);
            tmp.push_back(RotationMatrix[1][0]*toRotate.points[i][0] +RotationMatrix[1][1]*toRotate.points[i][1] + RotationMatrix[1][2]*toRotate.points[i][2]);
            tmp.push_back(RotationMatrix[2][0]*toRotate.points[i][0] +RotationMatrix[2][1]*toRotate.points[i][1] + RotationMatrix[2][2]*toRotate.points[i][2]);
            points.push_back(tmp);

            vector<float> tmp_norm;
            tmp_norm.push_back(RotationMatrix[0][0]*toRotate.normals[i][0] +RotationMatrix[0][1]*toRotate.normals[i][1] + RotationMatrix[0][2]*toRotate.normals[i][2]);
            tmp_norm.push_back(RotationMatrix[1][0]*toRotate.normals[i][0] +RotationMatrix[1][1]*toRotate.normals[i][1] + RotationMatrix[1][2]*toRotate.normals[i][2]);
            tmp_norm.push_back(RotationMatrix[2][0]*toRotate.normals[i][0] +RotationMatrix[2][1]*toRotate.normals[i][1] + RotationMatrix[2][2]*toRotate.normals[i][2]);
            normals.push_back(tmp_norm);
    }
    Surface s;
    s.points = points;
    s.normals = normals;
    s.size = toRotate.size;
    return s;

}
void print_buffer(){
 for(int y=H_size-1;y>=0;y--,printf("\n"))
        for(int x=0;x<W_size-1;x++,printf(" ")){
           printf("%c",printvals[a[x][y]]);
        }
}
void ResetDepthBuffer(){
    for(int x=0;x<W_size;x++)
        for(int y=0;y<H_size;y++)
            zbuf[x][y]=-1e19;
}
void init(){
    float w = sqrt(pow(light_source[0],2)+pow(light_source[1],2)+pow(light_source[2],2));
    light_source[0] = light_source[0]/w;
    light_source[1] = light_source[1]/w;
    light_source[2] = light_source[2]/w;
}
void setCursorPosition(int x,int y){
    static const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

    fflush(stdout);

    COORD coord = {(SHORT)x,(SHORT)y};
    SetConsoleCursorPosition(hout,coord);
}
int main(){
    init();
    Surface points_torus = Torus(6,3);
    for(int i=0;i<50;i++){
        setCursorPosition(0,0);
        ResetDepthBuffer();
        Surface points_torus_r = Rot(points_torus,i*10*3.14/180,0);
        points_torus_r = Rotz(points_torus_r,0,i*10*3.14/180);
        render(points_torus_r);
        print_buffer();
    }
}