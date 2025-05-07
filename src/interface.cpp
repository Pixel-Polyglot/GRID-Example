#include <iostream>
#include "pipelines/pipeline.h"

extern "C" int getVersionMajor() __attribute__((visibility("default")));
extern "C" int getVersionMinor() __attribute__((visibility("default")));
extern "C" void setWidgets() __attribute__((visibility("default")));
extern "C" void init() __attribute__((visibility("default")));
extern "C" void run() __attribute__((visibility("default")));
extern "C" void destroy() __attribute__((visibility("default")));

// add get version function
extern "C" int getVersionMajor() {
	return 0;
}

extern "C" int getVersionMinor() {
	return 1;
}

// add widgets function
extern "C" void setWidgets() {
}

// add args to init
extern "C" void init() {
	pipeline.init();
}

extern "C" void run() {
	pipeline.run();
}

extern "C" void destroy() {
	pipeline.destroy();
}