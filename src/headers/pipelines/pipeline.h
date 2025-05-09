#pragma once

#include <GRID/shaderProgram.h>
#include <gpu/gpu.h>
#include <imgui.h>

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

private:
    ComputeProgram gpuRender;
    GPU* gpu;
};

extern Pipeline pipeline;