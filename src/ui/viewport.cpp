#include "ui/viewport.h"
#include <GRID/renderer.h>

Viewport::Viewport() {
}

Viewport::~Viewport() {
}

void Viewport::render() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("Viewport", nullptr);

    ImGuiIO& io = ImGui::GetIO();
    if (ImGui::IsWindowHovered()) {
        if (io.MouseDown[0]) {
            ImVec2 mousePos = ImGui::GetMousePos();
            renderer.getCamera()->translate(mousePos.x - previousMousePos.x, mousePos.y - previousMousePos.y);
        }
        if (io.MouseWheel != 0.0f) {
			float scaleX, scaleY;
            renderer.getCamera()->getScale(scaleX, scaleY);
            float scrollAmount = io.MouseWheel * (scaleX * 0.1f);
            renderer.getCamera()->setScale(scaleX + scrollAmount, scaleY + scrollAmount);
        }
    }
	previousMousePos = ImGui::GetMousePos();

	ImVec2 newViewportPanelSize = ImGui::GetContentRegionAvail();
    if (newViewportPanelSize.x != viewportPanelSize.x || newViewportPanelSize.y != viewportPanelSize.y) {
        renderer.resize(int(viewportPanelSize.x), int(viewportPanelSize.y), int(newViewportPanelSize.x), int(newViewportPanelSize.y));
    }
    viewportPanelSize = newViewportPanelSize;
    renderer.render();
	ImGui::Image(
		(void*)renderer.getImguiTexture(),  
		ImVec2(viewportPanelSize.x, viewportPanelSize.y), 
		ImVec2(0, 1), 
		ImVec2(1, 0)
	);
	ImGui::End();

    ImGui::PopStyleVar(3);
}