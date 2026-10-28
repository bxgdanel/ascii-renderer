#pragma once
#include <vector>
#include <cmath>
using std::vector;
struct Ray {
 float origin[3];
 float direction[3];
};
class Camera {
  private:
    void rotate_z_by_angle(float p[3],float angle){
    float angleRadians = angle * static_cast<float>(M_PI) / 180.0f;
    
    float cosTheta = std::cos(angleRadians);
    float sinTheta = std::sin(angleRadians);

    // Păstrăm valorile inițiale într-un cache local
    float oldX = p[0];
    float oldY = p[1];

    // Aplicăm rotația direct pe elemente
    p[0] = oldX * cosTheta - oldY * sinTheta;
    p[1] = oldX * sinTheta + oldY * cosTheta;
    }
public:
  float Coords[3];
  float rotation_angle;
  Ray get_ray(int x, int y, int W_size, int H_size);
  Camera(float c[3]){Coords[0] = c[0], Coords[1] = c[1], Coords[2] = c[2];}
  Camera() {}
  void setPosition(float c[3]) {Coords[0] = c[0], Coords[1] = c[1], Coords[2] = c[2];}
};
