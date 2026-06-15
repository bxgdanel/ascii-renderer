#include "domain.h"
#include <vector>
void Torus::generate(vector<float> dim) {
  if (dim.size() != 2)
    // throw std::exception("Torus generator needs 2 dimensions: R, r");
    return;
  float R = dim[0], r = dim[1];
  for (float theta = 0; theta < 6.28; theta += 0.1)
    for (float phi = 0; phi < 6.28; phi += 0.1) {
      vector<float> tmp;
      vector<float> tmp_norm;
      tmp.push_back((R + r * cos(theta)) * cos(phi)); // x conform ec param
      tmp.push_back((R + r * cos(theta)) * sin(phi)); // y conform ec param
      tmp.push_back(r * sin(theta));

      tmp_norm.push_back(cos(theta) * cos(phi));
      tmp_norm.push_back(cos(theta) * sin(phi));
      tmp_norm.push_back(sin(theta));

      points.push_back(tmp);
      normals.push_back(tmp_norm);
    }
  size = points.size();
}
void Surface::rotate_x(float unghi) {
  float RotationMatrix[3][3] = {{1, 0, 0},
                                {0, (float)cos(unghi), -(float)sin(unghi)},
                                {0, (float)sin(unghi), (float)cos(unghi)}};
  vector<vector<float>> points_cpy;
  vector<vector<float>> normals_cpy;
  float xc, yc, zc;
  xc = center[0];
  yc = center[1];
  zc = center[2];
  this->translate(-xc, -yc, -zc);
  for (int i = 0; i < points.size(); i++) {
    vector<float> tmp;
    tmp.push_back(RotationMatrix[0][0] * this->points[i][0] +
                  RotationMatrix[0][1] * this->points[i][1] +
                  RotationMatrix[0][2] * this->points[i][2]);
    tmp.push_back(RotationMatrix[1][0] * this->points[i][0] +
                  RotationMatrix[1][1] * this->points[i][1] +
                  RotationMatrix[1][2] * this->points[i][2]);
    tmp.push_back(RotationMatrix[2][0] * this->points[i][0] +
                  RotationMatrix[2][1] * this->points[i][1] +
                  RotationMatrix[2][2] * this->points[i][2]);
    points_cpy.push_back(tmp);

    vector<float> tmp_norm;
    tmp_norm.push_back(RotationMatrix[0][0] * this->normals[i][0] +
                       RotationMatrix[0][1] * this->normals[i][1] +
                       RotationMatrix[0][2] * this->normals[i][2]);
    tmp_norm.push_back(RotationMatrix[1][0] * this->normals[i][0] +
                       RotationMatrix[1][1] * this->normals[i][1] +
                       RotationMatrix[1][2] * this->normals[i][2]);
    tmp_norm.push_back(RotationMatrix[2][0] * this->normals[i][0] +
                       RotationMatrix[2][1] * this->normals[i][1] +
                       RotationMatrix[2][2] * this->normals[i][2]);
    normals_cpy.push_back(tmp_norm);
  }

  points = points_cpy;
  normals = normals_cpy;
  this->translate(xc, yc, zc);
}
void Surface::rotate_z(float unghi) {
  float RotationMatrix[3][3] = {{(float)cos(unghi), -(float)sin(unghi), 0},
                                {(float)sin(unghi), (float)cos(unghi), 0},
                                {0, 0, 1}};
  vector<vector<float>> points_cpy;
  vector<vector<float>> normals_cpy;
  for (int i = 0; i < points.size(); i++) {
    vector<float> tmp;
    tmp.push_back(RotationMatrix[0][0] * this->points[i][0] +
                  RotationMatrix[0][1] * this->points[i][1] +
                  RotationMatrix[0][2] * this->points[i][2]);
    tmp.push_back(RotationMatrix[1][0] * this->points[i][0] +
                  RotationMatrix[1][1] * this->points[i][1] +
                  RotationMatrix[1][2] * this->points[i][2]);
    tmp.push_back(RotationMatrix[2][0] * this->points[i][0] +
                  RotationMatrix[2][1] * this->points[i][1] +
                  RotationMatrix[2][2] * this->points[i][2]);
    points_cpy.push_back(tmp);

    vector<float> tmp_norm;
    tmp_norm.push_back(RotationMatrix[0][0] * this->normals[i][0] +
                       RotationMatrix[0][1] * this->normals[i][1] +
                       RotationMatrix[0][2] * this->normals[i][2]);
    tmp_norm.push_back(RotationMatrix[1][0] * this->normals[i][0] +
                       RotationMatrix[1][1] * this->normals[i][1] +
                       RotationMatrix[1][2] * this->normals[i][2]);
    tmp_norm.push_back(RotationMatrix[2][0] * this->normals[i][0] +
                       RotationMatrix[2][1] * this->normals[i][1] +
                       RotationMatrix[2][2] * this->normals[i][2]);
    normals_cpy.push_back(tmp_norm);
  }
  points = points_cpy;
  normals = normals_cpy;
}
void Surface::translate(float x, float y, float z) {
  for (int i = 0; i < points.size(); i++) {
    this->points[i][0] += x;
    this->points[i][1] += y;
    this->points[i][2] += z;
  }
  this->center[0] += x, this->center[1] += y, this->center[2] += z;
}
bool Surface::intersect(Ray &ray, float &t, vector<float> &norm) const {
  bool hit = false;
  t = 1e9;
  float radius = .4f;
  if (norm.size() < 3)
    norm.resize(3);
  for (int i = 0; i < points.size(); i++) {
    float oc[3];
    oc[0] = (ray.origin[0] - points[i][0]);
    oc[1] = (ray.origin[1] - points[i][1]);
    oc[2] = (ray.origin[2] - points[i][2]);
    float b = 2.0f * (oc[0] * ray.direction[0] + oc[1] * ray.direction[1] +
                      oc[2] * ray.direction[2]);
    float c = (oc[0] * oc[0] + oc[1] * oc[1] + oc[2] * oc[2]) - radius * radius;
    float disc = b * b - 4.0f * c;
    if (disc >= 0) {
      float t1 = (-b - sqrt(disc)) / 2.0f;

      if (t1 > 0.001f && t1 < t)
        t = t1;
      if (i < normals.size() && !normals[i].empty())
        norm = normals[i];

      hit = true;
    }
  }
  return hit;
}
