#include <ui/sidebar.h>
#include <imgui.h>
#include <pipelines/pipeline.h>
#include <GRID/window.h>

Sidebar::Sidebar() {
}

Sidebar::~Sidebar() {
}

void Sidebar::render() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoResize);

    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Checkbox("V-Sync", &pipeline.vsync);

    ImGui::InputText("Filename", pipeline.fileName, 256);

    if (ImGui::Button("Save Image")) {
        pipeline.saveImage = true;
    };

	ImGui::End();

    ImGui::PopStyleVar(2);
}