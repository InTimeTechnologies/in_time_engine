#include "WindowManager.h"

// Dependencies | std
#include <cassert>

namespace it {
	// class WindowManager

	// Object | public

	// Functions
	Window* WindowManager::createWindow() {
		// iWindowPlatformBackend error check
		assert(iWindowPlatformBackend != nullptr && "iWindowPlatformBackend == nullptr");
		if (iWindowPlatformBackend == nullptr)
			return nullptr;

		// Create window and link backend
		Window& window = windowList.emplace_back();
		if (iWindowPlatformBackend != nullptr) {
			window.iWindowBackend = iWindowPlatformBackend->createWindowBackend(window);
		}
		return &window;
	}
	void WindowManager::destroyWindow(Window& window) {
		windowList.remove(window);
	}
}
