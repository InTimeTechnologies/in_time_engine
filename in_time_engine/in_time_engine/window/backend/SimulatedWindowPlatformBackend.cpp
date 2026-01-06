#include "SimulatedWindowPlatformBackend.h"

namespace it {
	// class SimulatedWindowPlatformBackend

	// Object | public

	// Functions
	IWindowBackend* SimulatedWindowPlatformBackend::createWindow() {
		return windowBackend;
	}
	void SimulatedWindowPlatformBackend::destroyWindow(IWindowBackend* iWindowBackend) {
		// Left empty intentionally
	}
}
