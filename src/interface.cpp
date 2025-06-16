#include "pipelines/pipeline.h"
#include <GRID/GRID.h>
#include <GRID/GRID_ui.h>
#include "ui/sidebar.h"
#include "ui/viewport.h"

extern "C" void setWidgets() {
	GRID_UI::addWidget(new Viewport());
    GRID_UI::addWidget(new Sidebar());
}

extern "C" void init(int argc, char* argv[]) {
	pipeline.init(argc, argv);
}

extern "C" void run() {
	pipeline.run();
}

extern "C" void destroy() {
	pipeline.destroy();
}