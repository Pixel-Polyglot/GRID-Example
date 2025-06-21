#include <gpu/gpu.h>
#include <cstring>
#undef min
#undef max
#include <algorithm>

GPU::GPU(){
}

GPU::~GPU(){
}

void GPU::init(GRID_Vec2i res) {

    m_imageSize = res;

    m_framebuffer = new unsigned char[m_imageSize.x * m_imageSize.y * 4]{0};

    m_triangles.push_back(triangle{vertex{GRID_Vec2f(40, 40), GRID_Vec3f(255, 0, 0)}, vertex{GRID_Vec2f(80, 40), GRID_Vec3f(0, 255, 0)}, vertex{GRID_Vec2f(40, 80), GRID_Vec3f(0, 0, 255)}});
    m_triangles.push_back(triangle{vertex{GRID_Vec2f(40, 80), GRID_Vec3f(255, 0, 0)}, vertex{GRID_Vec2f(80, 40), GRID_Vec3f(0, 255, 0)}, vertex{GRID_Vec2f(90, 90), GRID_Vec3f(0, 0, 255)}});
    m_triangles.push_back(triangle{vertex{GRID_Vec2f(40, 40), GRID_Vec3f(255, 0, 0)}, vertex{GRID_Vec2f(75, 20), GRID_Vec3f(0, 255, 0)}, vertex{GRID_Vec2f(80, 40), GRID_Vec3f(0, 0, 255)}});
}

unsigned char* GPU::run(){
    std::memset(m_framebuffer, 0, m_imageSize.x * m_imageSize.y * 4);

    std::vector<std::vector<std::vector<unsigned char>>> image;

    for (auto triangle : m_triangles) {
        // triangle bounding box
        int min_x = std::max(float(0),              std::min(std::min(triangle.a.position.x, triangle.b.position.x), triangle.c.position.x));
        int max_x = std::min(float(m_imageSize.x),    std::max(std::max(triangle.a.position.x, triangle.b.position.x), triangle.c.position.x));
        int min_y = std::max(float(0),              std::min(std::min(triangle.a.position.y, triangle.b.position.y), triangle.c.position.y));
        int max_y = std::min(float(m_imageSize.y),   std::max(std::max(triangle.a.position.y, triangle.b.position.y), triangle.c.position.y));
        
        // triangle edges
        GRID_Vec2f e1 = triangle.b.position - triangle.a.position;
        GRID_Vec2f e2 = triangle.c.position - triangle.b.position;
        GRID_Vec2f e3 = triangle.a.position - triangle.c.position;

        // bias for topleft rule
        int bias1 = ((e1.y == 0 && e1.x > 0) || e1.y < 0) ? 0 : -1;
        int bias2 = ((e2.y == 0 && e2.x > 0) || e2.y < 0) ? 0 : -1;
        int bias3 = ((e3.y == 0 && e3.x > 0) || e3.y < 0) ? 0 : -1;

        // triangle area for barycentric coordinates
        float area = edgecross(triangle.a.position, triangle.b.position, triangle.c.position);

        // backface culling
        if(area > 0) {
            // inverse area in order to only divide once
            float inv_area = 1.0f / area;
            // loop through pixels within bounding box
            for(int j = min_y; j <= max_y; j++) {
                for(int i = min_x; i <= max_x; i++) {
                    // check if part of triangle
                    float w1 = edgecross(GRID_Vec2f(i, j), triangle.a.position, triangle.b.position) + bias1;
                    float w2 = edgecross(GRID_Vec2f(i, j), triangle.b.position, triangle.c.position) + bias2;
                    float w3 = edgecross(GRID_Vec2f(i, j), triangle.c.position, triangle.a.position) + bias3;
                    if(w1 >= 0 && w2 >= 0 && w3 >= 0) {
                        // barycentric coordinates
                        float alpha = w2 * inv_area;
                        float beta = w3 * inv_area;
                        float gamma = w1 * inv_area;

                        // interpolate vertex colors
                        m_framebuffer[m_imageSize.x*4*j+i*4+0] = triangle.a.color.x * alpha + triangle.b.color.x * beta + triangle.c.color.x * gamma;
                        m_framebuffer[m_imageSize.x*4*j+i*4+1] = triangle.a.color.y * alpha + triangle.b.color.y * beta + triangle.c.color.y * gamma;
                        m_framebuffer[m_imageSize.x*4*j+i*4+2] = triangle.a.color.z * alpha + triangle.b.color.z * beta + triangle.c.color.z * gamma;
                        m_framebuffer[m_imageSize.x*4*j+i*4+3] = 255;
                    }
                }
            }
        }
    }

    return m_framebuffer;
}

int GPU::edgecross(GRID_Vec2f p, GRID_Vec2f a, GRID_Vec2f b) {
    GRID_Vec2f ab = b - a;
    GRID_Vec2f ap = p - a;

    return ab.x * ap.y - ab.y * ap.x;
}