#pragma once
#include <glm/glm.hpp>

struct vertex {
    glm::vec2 position;
    glm::vec3 color;
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
    int edgecross(glm::vec2 p, glm::vec2 a, glm::vec2 b);

    int image_width;
    int image_height;
    unsigned char* framebuffer;
    std::vector<triangle> triangles;
};