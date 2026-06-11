#pragma once
#include "renderer.h"

class PerspectiveRenderer:public Renderer{
    int fov;
    void render(const Surface* surface) override;
    void ResetDepthBuffer() override;
    public:
    PerspectiveRenderer(int width,int height,vector<float> light_source,int fov);
};