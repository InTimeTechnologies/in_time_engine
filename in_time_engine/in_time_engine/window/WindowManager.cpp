#include "WindowManager.h"

namespace it {
	// class WindowManager

	// Object | public

	// Functions
	Window& WindowManager::createWindow() {
		Window& window = windowList.emplace_back();
		return window;
	}
	Window& WindowManager::createWindow(int width, int height, const std::string& title) {
		Window& window = windowList.emplace_back(width, height, title);
		return window;
	}
	void WindowManager::destroyWindow(Window& window) {
		windowList.remove(window);
	}
}
