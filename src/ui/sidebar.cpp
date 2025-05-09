#include <ui/sidebar.h>
#include <imgui.h>
#include <pipelines/pipeline.h>
#include <GRID/window.h>
#include <implot.h>

Sidebar::Sidebar() {
}

Sidebar::~Sidebar() {
}

void Sidebar::render() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoResize);

    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    pipeline.fpsplotdelta += ImGui::GetIO().DeltaTime;
    if (pipeline.fpsplotdelta > 60.0) {
        pipeline.fpsplotdelta -= 60.0;
    }
    pipeline.fpsplotdata[int(pipeline.fpsplotdelta*10)] = ImGui::GetIO().Framerate;

    int fpsmax = 0;
    for (int i = 0; i < 600; i++) {
        if (pipeline.fpsplotdata[i] > fpsmax) {
            fpsmax = pipeline.fpsplotdata[i];
        }
    }
    
    // Axis flags
    ImPlotAxisFlags x_flags =
        ImPlotAxisFlags_NoTickLabels |
        ImPlotAxisFlags_NoLabel |
        ImPlotAxisFlags_Lock |
        ImPlotAxisFlags_NoHighlight;

    ImPlotAxisFlags y_flags =
        ImPlotAxisFlags_Lock |
        ImPlotAxisFlags_NoHighlight; // keep ticks and grid

    ImPlot::BeginPlot("##HiddenPlot", ImVec2(-1, 100));
    ImPlot::SetupAxes(nullptr, "##FPS", x_flags, y_flags);
    ImPlot::SetupAxesLimits(0, 600, 0, fpsmax*1.25, ImGuiCond_Always);
    ImPlot::PlotLine("##Line", pipeline.fpsplotdata, 600);
    ImPlot::EndPlot();

    ImGui::Checkbox("V-Sync", &pipeline.vsync);

    ImGui::InputText("Filename", pipeline.fileName, 256);

    if (ImGui::Button("Save Image")) {
        pipeline.saveImage = true;
    };

	ImGui::End();

    ImGui::PopStyleVar(2);
}