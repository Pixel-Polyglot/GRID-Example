#include <pipelines/pipeline.h>
#include <GRID/GRID_window.h>
#include <gpu/gpu.h>
#include <GRID/GRID_textures.h>
#include <ui/viewport.h>

Pipeline pipeline = Pipeline();

Pipeline::Pipeline() {
}

Pipeline::~Pipeline() {
}

const GRID_Vec2i GPURES = GRID_Vec2i(160, 160); 

void Pipeline::init(int argc, char* argv[]) {
    renderer = new GRID_Renderer();
    renderer->init("renderTexture");
    renderer->setResolution(GPURES);
    GRID_Textures::createTexture("gpuOutput", GPURES, GRID_TEXTUREFORMAT::RGBA8UI, 0);

    gpuRender.setComputeShaderFile("shaders/rendergpu.cs");
    gpuRender.compile();

    char image[GPURES.x*GPURES.y*4];
    for(int i = 0; i < GPURES.x*GPURES.y*4; i++) image[i] = 255;
    GRID_Textures::writeTexture("gpuOutput", GPURES, GRID_TEXTUREFORMAT::RGBA8UI, (int*)image);

    gpu = new GPU();
    gpu->init(GPURES);
}

void Pipeline::run() {
    GRID_Window::enableVsync(vsync);
    
    unsigned char* image = gpu->run();
    GRID_Textures::writeTexture("gpuOutput", GPURES, GRID_TEXTUREFORMAT::RGBA8UI, (int*)image);

    GRID_Vec2i texRes = renderer->getResolution();

    gpuRender.use();
    gpuRender.setImage("gpuOutput", "gpuOutput", GRID_TEXTUREFORMAT::RGBA8UI);
    gpuRender.setImage("renderTexture", renderer->getTextureName(), GRID_TEXTUREFORMAT::RGBA32F);
    gpuRender.compute(texRes.x / 16, texRes.y / 16, 1);

    if (saveImage) {
        GRID_Textures::saveTextureToFile("gpuOutput", fileName, texRes, GRID_TEXTUREFORMAT::RGBA8UI);
        saveImage = false;
    }
}

void Pipeline::destroy() {
    renderer->destroy();
}