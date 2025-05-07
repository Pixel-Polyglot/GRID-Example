#pragma once

#include <GRID/shaderProgram.h>
#include <gpu/gpu.h>

class Pipeline {
public:
    Pipeline();
    ~Pipeline();

    void init();
    void run();
    void destroy();

    bool vsync = true;
    char fileName[256];
    bool saveImage = false;

private:
    ComputeProgram gpuRender;
    GPU* gpu;
};

extern Pipeline pipeline;