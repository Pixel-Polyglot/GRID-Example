#include "ui/viewport.h"
#include <GRID/GRID_renderer.h>
#include <GRID/GRID_ui.h>
#include <GRID/GRID_input.h>
#include <pipelines/pipeline.h>

Viewport::Viewport() {
}

Viewport::~Viewport() {
}

void Viewport::render() {
    GRID_UI::begin("Viewport", false);

    if (GRID_UI::isWindowHovered()) {
        if (GRID_Input::isMouseButtonDown(GRID_Input::MOUSE_BUTTON_LEFT)) {
            GRID_Vec2f mousePos = GRID_Input::getMousePos();
            pipeline.renderer->getCamera()->translate(mousePos - previousMousePos);
        }
        if (GRID_Input::getMouseWheel() != 0.0f) {
            GRID_Vec2f scale = pipeline.renderer->getCamera()->getScale();
            float scrollAmount = GRID_Input::getMouseWheel() * (scale.x * 0.1f);
            pipeline.renderer->getCamera()->setScale(scale + scrollAmount);
        }
    }
	previousMousePos = GRID_Input::getMousePos();

	GRID_Vec2f newViewportPanelSize = GRID_UI::getContentRegionAvail();
    if (newViewportPanelSize.x != viewportPanelSize.x || newViewportPanelSize.y != viewportPanelSize.y) {
        pipeline.renderer->resize(GRID_Vec2i(viewportPanelSize.x, viewportPanelSize.y), GRID_Vec2i(newViewportPanelSize.x, newViewportPanelSize.y));
    }
    viewportPanelSize = newViewportPanelSize;
    pipeline.renderer->render();
	GRID_UI::image(
		(void*)pipeline.renderer->getGuiTexture(),  
		GRID_Vec2f(viewportPanelSize.x, viewportPanelSize.y), 
		GRID_Vec2f(0, 1), 
		GRID_Vec2f(1, 0)
	);

	GRID_UI::end();
}