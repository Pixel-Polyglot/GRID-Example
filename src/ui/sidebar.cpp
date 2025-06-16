#include <ui/sidebar.h>
#include <pipelines/pipeline.h>
#include <GRID/GRID_window.h>
#include <GRID/GRID_ui.h>

Sidebar::Sidebar() {
}

Sidebar::~Sidebar() {
}

void Sidebar::render() {
    GRID_UI::begin("Menu");

    GRID_UI::text("%.3f ms/frame (%.1f FPS)", GRID_Window::getDeltaTime() * 1000, 1.0f / GRID_Window::getDeltaTime());

    // pipeline.fpsplotdelta += ImGui::GetIO().DeltaTime;
    // if (pipeline.fpsplotdelta > 60.0) {
    //     pipeline.fpsplotdelta -= 60.0;
    // }
    // pipeline.fpsplotdata[int(pipeline.fpsplotdelta*10)] = ImGui::GetIO().Framerate;

    // int fpsmax = 0;
    // for (int i = 0; i < 600; i++) {
    //     if (pipeline.fpsplotdata[i] > fpsmax) {
    //         fpsmax = pipeline.fpsplotdata[i];
    //     }
    // }
    
    // // Axis flags
    // ImPlotAxisFlags x_flags =
    //     ImPlotAxisFlags_NoTickLabels |
    //     ImPlotAxisFlags_NoLabel |
    //     ImPlotAxisFlags_Lock |
    //     ImPlotAxisFlags_NoHighlight;

    // ImPlotAxisFlags y_flags =
    //     ImPlotAxisFlags_Lock |
    //     ImPlotAxisFlags_NoHighlight; // keep ticks and grid

    // ImPlot::BeginPlot("##HiddenPlot", ImVec2(-1, 100));
    // ImPlot::SetupAxes(nullptr, "##FPS", x_flags, y_flags);
    // ImPlot::SetupAxesLimits(0, 600, 0, fpsmax*1.25, ImGuiCond_Always);
    // ImPlot::PlotLine("##Line", pipeline.fpsplotdata, 600);
    // ImPlot::EndPlot();

    GRID_UI::checkbox("V-Sync", &pipeline.vsync);

    GRID_UI::inputText("Filename", pipeline.fileName, 256);

    if (GRID_UI::button("Save Image")) {
        pipeline.saveImage = true;
    };

	GRID_UI::end();
}