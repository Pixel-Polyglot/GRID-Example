#include <pipelines/pipeline.h>
#include <GRID/renderer.h>
#include <GRID/window.h>
#include <GRID/ui.h>
#include "ui/viewport.h"
#include "ui/sidebar.h"
#include <gpu/gpu.h>

Pipeline pipeline = Pipeline();

Pipeline::Pipeline() {
}

Pipeline::~Pipeline() {
}

const int GPURESX = 160;
const int GPURESY = 160;

void Pipeline::init() {
    renderer.setResolution(GPURESX, GPURESY);
    textureManager.createTexture("gpuOutput", GPURESX, GPURESY, TEXTURE_FORMAT::RGBA8UI, 0);

    gpuRender.setComputeShader("../shaders/rendergpu.cs");
    gpuRender.compile();

    char image[GPURESX*GPURESY*4];
    for(int i = 0; i < GPURESX*GPURESY*4; i++) image[i] = 255;
    textureManager.writeTexture("gpuOutput", GPURESX, GPURESY, TEXTURE_FORMAT::RGBA8UI, (int*)image);

    gpu = new GPU();
    gpu->init(GPURESX, GPURESY);

    ui.addWidget(new Viewport());
    ui.addWidget(new Sidebar());
}

void Pipeline::run() {
    window.enableVsync(vsync);
    
    unsigned char* image = gpu->run();
    textureManager.writeTexture("gpuOutput", GPURESX, GPURESY, TEXTURE_FORMAT::RGBA8UI, (int*)image);

    unsigned int width, height;
    renderer.getResolution(width, height);

    gpuRender.use();
    gpuRender.setImage("gpuOutput", "gpuOutput", TEXTURE_FORMAT::RGBA8UI);
    gpuRender.setImage("renderTexture", "renderTexture", TEXTURE_FORMAT::RGBA32F);
    gpuRender.compute(width / 16, height / 16, 1);

    if (saveImage) {
        textureManager.saveTextureToFile("gpuOutput", fileName, width, height, TEXTURE_FORMAT::RGBA8UI, 0, 0);
        saveImage = false;
    }
}

void Pipeline::destroy() {
}