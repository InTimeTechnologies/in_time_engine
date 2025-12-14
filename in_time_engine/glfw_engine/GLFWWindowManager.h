#pragma once

// Dependencies | std
#include <list>

// Dependencies | glfw_engine
#include "GLFWWindow.h"

namespace glfw {
	class WindowManager {
		// Friends
		friend class Engine;

		// Object
	public:
		// Properties
		std::list<Window> windows{};

		// Functions
		Window& createWindow();
		Window& createWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
		void destroyWindow(Window& window);
		void pollEvents();
	};
}