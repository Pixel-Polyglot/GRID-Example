#include "pipelines/pipeline.h"
#include <GRID/interface.h>
#include <GRID/ui.h>
#include "ui/sidebar.h"
#include "ui/viewport.h"

extern "C" void setWidgets() {
	ui.addWidget(new Viewport());
    ui.addWidget(new Sidebar());
}

// add args to init
extern "C" void init(int argc, char* argv[]) {
	pipeline.init(argc, argv);
}

extern "C" void run() {
	pipeline.run();
}

extern "C" void destroy() {
	pipeline.destroy();
}