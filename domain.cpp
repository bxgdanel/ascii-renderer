#include "domain.h"
void Torus::generate(vector<float> dim){
    if(dim.size()!=2)
        //throw std::exception("Torus generator needs 2 dimensions: R, r");
        return;
    float R=dim[0],r=dim[1];
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
    size = points.size();
}
void Surface::rotate_x(float unghi){
    float RotationMatrix[3][3]={{1,0,0},{0,cos(unghi),-sin(unghi)},{0,sin(unghi),cos(unghi)}};
    vector<vector<float>> points_cpy;
    vector<vector<float>> normals_cpy;
    float xc,yc,zc;
    xc = center[0];
    yc=center[1];
    zc=center[2];
    this->translate(-xc,-yc,-zc);
    for(int i =0;i<this->size;i++){
            vector<float> tmp;
            tmp.push_back(RotationMatrix[0][0]*this->points[i][0] +RotationMatrix[0][1]*this->points[i][1] + RotationMatrix[0][2]*this->points[i][2]);
            tmp.push_back(RotationMatrix[1][0]*this->points[i][0] +RotationMatrix[1][1]*this->points[i][1] + RotationMatrix[1][2]*this->points[i][2]);
            tmp.push_back(RotationMatrix[2][0]*this->points[i][0] +RotationMatrix[2][1]*this->points[i][1] + RotationMatrix[2][2]*this->points[i][2]);
            points_cpy.push_back(tmp);

            vector<float> tmp_norm;
            tmp_norm.push_back(RotationMatrix[0][0]*this->normals[i][0] +RotationMatrix[0][1]*this->normals[i][1] + RotationMatrix[0][2]*this->normals[i][2]);
            tmp_norm.push_back(RotationMatrix[1][0]*this->normals[i][0] +RotationMatrix[1][1]*this->normals[i][1] + RotationMatrix[1][2]*this->normals[i][2]);
            tmp_norm.push_back(RotationMatrix[2][0]*this->normals[i][0] +RotationMatrix[2][1]*this->normals[i][1] + RotationMatrix[2][2]*this->normals[i][2]);
            normals_cpy.push_back(tmp_norm);
    }
   
    points = points_cpy;
    normals = normals_cpy;
    this->translate(xc,yc,zc);
}
void Surface::rotate_z(float unghi){
    float RotationMatrix[3][3]={{cos(unghi),-sin(unghi),0},{sin(unghi),cos(unghi),0},{0,0,1}};
    vector<vector<float>> points_cpy;
    vector<vector<float>> normals_cpy;
    for(int i =0;i<this->size;i++){
            vector<float> tmp;
            tmp.push_back(RotationMatrix[0][0]*this->points[i][0] +RotationMatrix[0][1]*this->points[i][1] + RotationMatrix[0][2]*this->points[i][2]);
            tmp.push_back(RotationMatrix[1][0]*this->points[i][0] +RotationMatrix[1][1]*this->points[i][1] + RotationMatrix[1][2]*this->points[i][2]);
            tmp.push_back(RotationMatrix[2][0]*this->points[i][0] +RotationMatrix[2][1]*this->points[i][1] + RotationMatrix[2][2]*this->points[i][2]);
            points_cpy.push_back(tmp);

            vector<float> tmp_norm;
            tmp_norm.push_back(RotationMatrix[0][0]*this->normals[i][0] +RotationMatrix[0][1]*this->normals[i][1] + RotationMatrix[0][2]*this->normals[i][2]);
            tmp_norm.push_back(RotationMatrix[1][0]*this->normals[i][0] +RotationMatrix[1][1]*this->normals[i][1] + RotationMatrix[1][2]*this->normals[i][2]);
            tmp_norm.push_back(RotationMatrix[2][0]*this->normals[i][0] +RotationMatrix[2][1]*this->normals[i][1] + RotationMatrix[2][2]*this->normals[i][2]);
            normals_cpy.push_back(tmp_norm);
    }
    points = points_cpy;
    normals = normals_cpy;
}
void Surface::translate(float x,float y,float z){
    for(int i =0;i<this->size;i++){
        this->points[i][0]+=x;
        this->points[i][1]+=y;
        this->points[i][2]+=z;
    }
    this->center[0]+=x,this->center[1]+=y,this->center[2]+=z;
}