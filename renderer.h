#pragma once
#include <vector>
#include <string>
#include "domain.h"
using std::vector;
class Renderer{
    protected:
    int W_size,H_size;
    vector<vector<int>>a;
    vector<vector<float>>zbuf;
    vector<const Surface*> shapes;
    vector<float>light_source;
    const std::string printvals = " .,-~:;=!*#$%@";
    const int printvals_len = 14;    
    void print_buffer();
    virtual void ResetDepthBuffer();
    void setCursorPosition(int x,int y);
    virtual void render(const Surface* surface);
    public:
    Renderer(int width,int height,vector<float> light_source);
    Renderer(){}
    void display();
    void add_shape(const Surface* s);
};