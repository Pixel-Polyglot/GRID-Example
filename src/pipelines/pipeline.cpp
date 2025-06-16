#include <pipelines/pipeline.h>
#include <GRID/GRID_renderer.h>
#include <GRID/GRID_window.h>
#include <gpu/gpu.h>
#include <GRID/GRID_textures.h>

Pipeline pipeline = Pipeline();

Pipeline::Pipeline() {
}

Pipeline::~Pipeline() {
}

const int GPURESX = 160;
const int GPURESY = 160;

void Pipeline::init(int argc, char* argv[]) {
    GRID_Renderer::setResolution(GPURESX, GPURESY);
    GRID_Textures::createTexture("gpuOutput", GPURESX, GPURESY, GRID_TEXTUREFORMAT::RGBA8UI, 0);

    gpuRender.setComputeShader("../shaders/rendergpu.cs");
    gpuRender.compile();

    char image[GPURESX*GPURESY*4];
    for(int i = 0; i < GPURESX*GPURESY*4; i++) image[i] = 255;
    GRID_Textures::writeTexture("gpuOutput", GPURESX, GPURESY, GRID_TEXTUREFORMAT::RGBA8UI, (int*)image);

    gpu = new GPU();
    gpu->init(GPURESX, GPURESY);
}

void Pipeline::run() {
    GRID_Window::enableVsync(vsync);
    
    unsigned char* image = gpu->run();
    GRID_Textures::writeTexture("gpuOutput", GPURESX, GPURESY, GRID_TEXTUREFORMAT::RGBA8UI, (int*)image);

    unsigned int width, height;
    GRID_Renderer::getResolution(width, height);

    gpuRender.use();
    gpuRender.setImage("gpuOutput", "gpuOutput", GRID_TEXTUREFORMAT::RGBA8UI);
    gpuRender.setImage("renderTexture", "renderTexture", GRID_TEXTUREFORMAT::RGBA32F);
    gpuRender.compute(width / 16, height / 16, 1);

    if (saveImage) {
        GRID_Textures::saveTextureToFile("gpuOutput", fileName, width, height, GRID_TEXTUREFORMAT::RGBA8UI, 0, 0);
        saveImage = false;
    }
}

void Pipeline::destroy() {
}