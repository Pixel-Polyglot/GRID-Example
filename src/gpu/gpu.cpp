#include <gpu/gpu.h>
#include <cstring>

GPU::GPU(){
}

GPU::~GPU(){
}

void GPU::init(int resX, int resY){
    image_width = resX;
    image_height = resY;

    framebuffer = new unsigned char[resX * resY * 4]{0};
    
    triangles.push_back(triangle{vertex{glm::vec2(40, 40), glm::vec3(255, 0, 0)}, vertex{glm::vec2(80, 40), glm::vec3(0, 255, 0)}, vertex{glm::vec2(40, 80), glm::vec3(0, 0, 255)}});
    triangles.push_back(triangle(vertex{glm::vec2(40, 80), glm::vec3(255, 0, 0)}, vertex{glm::vec2(80, 40), glm::vec3(0, 255, 0)}, vertex{glm::vec2(90, 90), glm::vec3(0, 0, 255)}));
    triangles.push_back(triangle(vertex{glm::vec2(40, 40), glm::vec3(255, 0, 0)}, vertex{glm::vec2(75, 20), glm::vec3(0, 255, 0)}, vertex{glm::vec2(80, 40), glm::vec3(0, 0, 255)}));
}

unsigned char* GPU::run(){
    std::memset(framebuffer, 0, image_width * image_height * 4);

    std::vector<std::vector<std::vector<unsigned char>>> image;

    for (auto triangle : triangles) {
        // triangle bounding box
        int min_x = std::max(float(0), std::min(std::min(triangle.a.position.x, triangle.b.position.x), triangle.c.position.x));
        int max_x = std::min(float(image_width), std::max(std::max(triangle.a.position.x, triangle.b.position.x), triangle.c.position.x));
        int min_y = std::max(float(0), std::min(std::min(triangle.a.position.y, triangle.b.position.y), triangle.c.position.y));
        int max_y = std::min(float(image_height), std::max(std::max(triangle.a.position.y, triangle.b.position.y), triangle.c.position.y));
        
        // triangle edges
        glm::vec2 e1 = triangle.b.position - triangle.a.position;
        glm::vec2 e2 = triangle.c.position - triangle.b.position;
        glm::vec2 e3 = triangle.a.position - triangle.c.position;

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
                    float w1 = edgecross(glm::vec2(i, j), triangle.a.position, triangle.b.position) + bias1;
                    float w2 = edgecross(glm::vec2(i, j), triangle.b.position, triangle.c.position) + bias2;
                    float w3 = edgecross(glm::vec2(i, j), triangle.c.position, triangle.a.position) + bias3;
                    if(w1 >= 0 && w2 >= 0 && w3 >= 0) {
                        // barycentric coordinates
                        float alpha = w2 * inv_area;
                        float beta = w3 * inv_area;
                        float gamma = w1 * inv_area;

                        // interpolate vertex colors
                        framebuffer[image_width*4*j+i*4+0] = triangle.a.color.r * alpha + triangle.b.color.r * beta + triangle.c.color.r * gamma;
                        framebuffer[image_width*4*j+i*4+1] = triangle.a.color.g * alpha + triangle.b.color.g * beta + triangle.c.color.g * gamma;
                        framebuffer[image_width*4*j+i*4+2] = triangle.a.color.b * alpha + triangle.b.color.b * beta + triangle.c.color.b * gamma;
                        framebuffer[image_width*4*j+i*4+3] = 255;
                    }
                }
            }
        }
    }

    return framebuffer;
}

int GPU::edgecross(glm::vec2 p, glm::vec2 a, glm::vec2 b) {
    glm::vec2 ab = b - a;
    glm::vec2 ap = p - a;

    return ab.x * ap.y - ab.y * ap.x;
}