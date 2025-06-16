#include "ui/viewport.h"
#include <GRID/GRID_renderer.h>
#include <GRID/GRID_ui.h>
#include <GRID/GRID_input.h>

Viewport::Viewport() {
}

Viewport::~Viewport() {
}

void Viewport::render() {
    GRID_UI::begin("Viewport");

    if (GRID_UI::isWindowHovered()) {
        if (GRID_Input::isMouseButtonDown(GRID_Input::MOUSE_BUTTON_LEFT)) {
            GRID_Vec2f mousePos = GRID_Input::getMousePos();
            GRID_Renderer::getCamera()->translate(mousePos.x - previousMousePos.x, mousePos.y - previousMousePos.y);
        }
        if (GRID_Input::getMouseWheel() != 0.0f) {
			float scaleX, scaleY;
            GRID_Renderer::getCamera()->getScale(scaleX, scaleY);
            float scrollAmount = GRID_Input::getMouseWheel() * (scaleX * 0.1f);
            GRID_Renderer::getCamera()->setScale(scaleX + scrollAmount, scaleY + scrollAmount);
        }
    }
	previousMousePos = GRID_Input::getMousePos();

	GRID_Vec2f newViewportPanelSize = GRID_UI::getContentRegionAvail();
    if (newViewportPanelSize.x != viewportPanelSize.x || newViewportPanelSize.y != viewportPanelSize.y) {
        GRID_Renderer::resize(int(viewportPanelSize.x), int(viewportPanelSize.y), int(newViewportPanelSize.x), int(newViewportPanelSize.y));
    }
    viewportPanelSize = newViewportPanelSize;
    GRID_Renderer::render();
	GRID_UI::image(
		(void*)GRID_Renderer::getGuiTexture(),  
		GRID_Vec2f(viewportPanelSize.x, viewportPanelSize.y), 
		GRID_Vec2f(0, 1), 
		GRID_Vec2f(1, 0)
	);

	GRID_UI::end();
}