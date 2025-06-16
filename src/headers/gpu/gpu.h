#pragma once

#include <GRID/GRID_math.h>
#include <vector>

struct vertex {
    GRID_Vec2f position;
    GRID_Vec3f color;
};

struct triangle {
    vertex a;
    vertex b;
    vertex c;
};

class GPU
{
public:
    GPU();
    ~GPU();
    void init(int resX, int resY);
    unsigned char* run();

private:
    int edgecross(GRID_Vec2f p, GRID_Vec2f a, GRID_Vec2f b);

    int image_width;
    int image_height;
    unsigned char* framebuffer;
    std::vector<triangle> triangles;
};