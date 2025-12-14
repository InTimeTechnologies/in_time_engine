#include "GLFWWindowManager.h"

namespace glfw {
	// class WindowManager

	// Object | public

	Window& WindowManager::createWindow() {
		windows.emplace_back();
		return windows.back();
	}
	Window& WindowManager::createWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
		windows.emplace_back(width, height, title, monitor, share);
		return windows.back();
	}
	void WindowManager::destroyWindow(Window& window) {
		windows.remove(window);
	}
	void WindowManager::pollEvents() {
		glfwPollEvents();
	}
}
