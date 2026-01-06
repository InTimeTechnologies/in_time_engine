#include "NullWindowPlatformBackend.h"

namespace it {
	// class NullWindowBackend

	// Object | public

	// Functions
	IWindowBackend* NullWindowPlatformBackend::createWindow() {
		return nullptr;
	};
	void NullWindowPlatformBackend::destroyWindow(IWindowBackend* iWindowBackend) {
		// Left empty intentionally
	};
}
