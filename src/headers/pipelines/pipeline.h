#pragma once

#include <gpu/gpu.h>
#include <GRID/GRID_renderer.h>
#include <GRID/GRID_shaderProgram.h>

class Pipeline {
public:
    Pipeline();
    ~Pipeline();

    void init(int argc, char* argv[]);
    void run();
    void destroy();

    bool vsync = true;
    char fileName[256];
    bool saveImage = false;

    float fpsplotdelta = 0.0f;
    float fpsplotdata[600];

    GRID_Renderer* renderer;

private:
    GRID_ComputeProgram gpuRender;
    GPU* gpu;
};

extern Pipeline pipeline;