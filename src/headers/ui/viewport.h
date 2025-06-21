#pragma once
#include <GRID/GRID_widget.h>
#include <GRID/GRID_math.h>
#include <GRID/GRID_renderer.h>

class Viewport : public GRID_Widget {
public:
    Viewport();
    ~Viewport();
    void render();

private:
    GRID_Vec2f viewportPanelSize = GRID_Vec2f(1.0f, 1.0f);
    GRID_Vec2f previousMousePos = GRID_Vec2f(0.0f, 0.0f);
};