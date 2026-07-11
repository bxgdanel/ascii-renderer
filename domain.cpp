#include "domain.h"
#include "PerspectiveRenderer.h"
// #include "renderer.h"
void Torus::generate() {
  float R = dim_r, r = dim_r;
  for (float theta = 0; theta < 6.28; theta += 0.03)
    for (float phi = 0; phi < 6.28; phi += 0.03) {
      vector<float> tmp;
      vector<float> tmp_norm;
      tmp.push_back((R + r * cos(theta)) * cos(phi)); // x conform ec param
      tmp.push_back((R + r * cos(theta)) * sin(phi)); // y conform ec param
      tmp.push_back(r * sin(theta));

      tmp_norm.push_back(cos(theta) * cos(phi));
      tmp_norm.push_back(cos(theta) * sin(phi));
      tmp_norm.push_back(sin(theta));
      colors.push_back(Color{255, 255, 255});
      points.push_back(tmp);
      normals.push_back(tmp_norm);
    }
  size = points.size();
}
void Surface::rotate_x(float unghi) {
  float RotationMatrix[3][3] = {
      {1, 0, 0},
      {0, static_cast<float>(cos(unghi)), static_cast<float>(-sin(unghi))},
      {0, static_cast<float>(sin(unghi)), static_cast<float>(cos(unghi))}};
  vector<vector<float>> points_cpy;
  vector<vector<float>> normals_cpy;
  float xc, yc, zc;
  xc = center[0];
  yc = center[1];
  zc = center[2];
  this->translate(-xc, -yc, -zc);
  for (int i = 0; i < this->size; i++) {
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
void Surface::rotate_x_pivot(float unghi, float x_, float y_, float z_) {
  float RotationMatrix[3][3] = {
      {1, 0, 0},
      {0, static_cast<float>(cos(unghi)), static_cast<float>(-sin(unghi))},
      {0, static_cast<float>(sin(unghi)), static_cast<float>(cos(unghi))}};
  vector<vector<float>> points_cpy;
  vector<vector<float>> normals_cpy;
  this->translate(-x_, -y_, -z_);
  for (int i = 0; i < this->size; i++) {
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
  float cx = this->center[0];
  float cy = this->center[1];
  float cz = this->center[2];
  this->center[0] = RotationMatrix[0][0] * cx + RotationMatrix[0][1] * cy +
                    RotationMatrix[0][2] * cz;
  this->center[1] = RotationMatrix[1][0] * cx + RotationMatrix[1][1] * cy +
                    RotationMatrix[1][2] * cz;
  this->center[2] = RotationMatrix[2][0] * cx + RotationMatrix[2][1] * cy +
                    RotationMatrix[2][2] * cz;
  points = points_cpy;
  normals = normals_cpy;
  this->translate(x_, y_, z_);
}
void Surface::rotate_z(float unghi) {
  float RotationMatrix[3][3] = {
      {static_cast<float>(cos(unghi)), static_cast<float>(-sin(unghi)), 0},
      {static_cast<float>(sin(unghi)), static_cast<float>(cos(unghi)), 0},
      {0, 0, 1}};
  vector<vector<float>> points_cpy;
  vector<vector<float>> normals_cpy;
  float xc, yc, zc;
  xc = center[0];
  yc = center[1];
  zc = center[2];
  this->translate(-xc, -yc, -zc);
  for (int i = 0; i < this->size; i++) {
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
void Surface::rotate_y_pivot(float unghi, float xc, float yc, float zc) {
  float RotationMatrix[3][3] = {
      {static_cast<float>(cos(unghi)), 0, static_cast<float>(sin(unghi))},
      {0, 1, 0},
      {static_cast<float>(-sin(unghi)), 0, static_cast<float>(cos(unghi))}};

  vector<vector<float>> points_cpy;
  vector<vector<float>> normals_cpy;
  this->translate(-xc, -yc, -zc);

  for (int i = 0; i < this->size; i++) {
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

  float cx = this->center[0];
  float cy = this->center[1];
  float cz = this->center[2];
  this->center[0] = RotationMatrix[0][0] * cx + RotationMatrix[0][1] * cy +
                    RotationMatrix[0][2] * cz;
  this->center[1] = RotationMatrix[1][0] * cx + RotationMatrix[1][1] * cy +
                    RotationMatrix[1][2] * cz;
  this->center[2] = RotationMatrix[2][0] * cx + RotationMatrix[2][1] * cy +
                    RotationMatrix[2][2] * cz;

  points = points_cpy;
  normals = normals_cpy;
  this->translate(xc, yc, zc);
}
void Surface::rotate_z_pivot(float unghi, float xc, float yc, float zc) {
  float RotationMatrix[3][3] = {
      {static_cast<float>(cos(unghi)), static_cast<float>(-sin(unghi)), 0},
      {static_cast<float>(sin(unghi)), static_cast<float>(cos(unghi)), 0},
      {0, 0, 1}};
  vector<vector<float>> points_cpy;
  vector<vector<float>> normals_cpy;
  this->translate(-xc, -yc, -zc);
  for (int i = 0; i < this->size; i++) {
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
  float cx = this->center[0];
  float cy = this->center[1];
  float cz = this->center[2];
  this->center[0] = RotationMatrix[0][0] * cx + RotationMatrix[0][1] * cy +
                    RotationMatrix[0][2] * cz;
  this->center[1] = RotationMatrix[1][0] * cx + RotationMatrix[1][1] * cy +
                    RotationMatrix[1][2] * cz;
  this->center[2] = RotationMatrix[2][0] * cx + RotationMatrix[2][1] * cy +
                    RotationMatrix[2][2] * cz;
  points = points_cpy;
  normals = normals_cpy;
  this->translate(xc, yc, zc);
}
void Surface::translate(float x, float y, float z) {
  for (int i = 0; i < this->size; i++) {
    this->points[i][0] += x;
    this->points[i][1] += y;
    this->points[i][2] += z;
  }
  this->center[0] += x, this->center[1] += y, this->center[2] += z;
}
void Cube::generate() {
  float step = .25f;
  for (float z = -h / 2.0f; z <= h / 2.0f + 0.001f; z += step)
    for (float y = -l / 2.0f; y <= l / 2.0f + 0.001f; y += step)
      for (float x = -w / 2.0f; x <= w / 2.0f + 0.001f; x += step) {

        bool isSurface = (std::abs(x) >= w / 2.0f - 0.01f ||
                          std::abs(y) >= l / 2.0f - 0.01f ||
                          std::abs(z) >= h / 2.0f - 0.01f);

        if (!isSurface) {
          continue;
        }

        vector<float> tmp;
        tmp.push_back(x);
        tmp.push_back(y);
        tmp.push_back(z);

        float nx = 0, ny = 0, nz = 0;
        float absX = std::abs(x);
        float absY = std::abs(y);
        float absZ = std::abs(z);

        Color c;

        if (absX >= absY && absX >= absZ) {
          if (x > 0) {
            nx = 1.0;
            c = Color{0, 255, 0};
          } else {
            nx = -1.0;
            c = Color{0, 0, 255};
          }
        } else if (absY >= absX && absY >= absZ) {
          if (y > 0) {
            ny = 1.0;
            c = Color(255, 255, 255);
          } else {
            ny = -1.0;
            c = Color(255, 255, 0);
          }
        } else {
          if (z > 0) {
            nz = 1.0;
            c = Color{255, 165, 0};
          } else {
            nz = -1.0;
            c = Color{255, 0, 0};
          }
        }
        vector<float> tmp_normals;
        tmp_normals.push_back(nx);
        tmp_normals.push_back(ny);
        tmp_normals.push_back(nz);

        points.push_back(tmp);
        normals.push_back(tmp_normals);
        colors.push_back(c);
      }
  size = points.size();
}
void Rubik::generate() {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 9; j++) {
      cubes[i * 9 + j].generate();
      cubes[i * 9 + j].translate((j % 3) * 10, (j / 3) * 10, i * 10);
    }
  this->center[0] = 10.0f;
  this->center[1] = 10.0f;
  this->center[2] = 10.0f;
  size = points.size();
}
void Rubik::translate(float x, float y, float z) {
  for (auto &c : cubes)
    c.translate(x, y, z);
  this->center[0] += x;
  this->center[1] += y;
  this->center[2] += z;
}
void Rubik::register_cubes(PerspectiveRenderer *r) {
  for (int i = 0; i < 27; i++) {
    r->add_shape(&cubes[i]);
  }
}
void Rubik::rotate_layer_x(int layer, float unghi) {
  float target_x = this->center[0] + layer * 10.0f;
  for (auto &c : cubes)
    if (std::abs(c.center[0] - target_x) < 1.0f)
      c.rotate_x_pivot(unghi, this->center[0], this->center[1],
                       this->center[2]);
}
void Rubik::rotate_layer_y(int layer, float unghi) {
  float target_x = this->center[1] + layer * 10.0f;
  for (auto &c : cubes)
    if (std::abs(c.center[1] - target_x) < 1.0f)
      c.rotate_y_pivot(unghi, this->center[0], this->center[1],
                       this->center[2]);
}

void Rubik::rotate_layer_z(int layer, float unghi) {
  float target_x = this->center[2] + layer * 10.0f;
  for (auto &c : cubes)
    if (std::abs(c.center[2] - target_x) < 1.0f)
      c.rotate_z_pivot(unghi, this->center[0], this->center[1],
                       this->center[2]);
}
void Rubik::R(int sens) {
  float val = M_PI / 2;
  for (int i = 0; i < 10; i++) {

    rotate_layer_x(1, sens * (val / 10));
    ren->display();
  }
}
void Rubik::U(int sens) {
  float val = M_PI / 2;
  for (int i = 0; i < 10; i++) {

    rotate_layer_y(1, sens * (val / 10));
    ren->display();
  }
}
