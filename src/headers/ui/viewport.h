#pragma once
#include <imgui.h>
#include <GRID/widget.h>

class Viewport : public Widget {
public:
    Viewport();
    ~Viewport();
    void render();

private:
    ImVec2 viewportPanelSize = ImVec2(1.0f, 1.0f);
    ImVec2 previousMousePos = ImVec2(0.0f, 0.0f);
};