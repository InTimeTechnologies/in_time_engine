#pragma once

// Dependencies | std
#include <list>
#include <string>

// Dependencies | in_time_engine | window
#include "Window.h"

namespace it {
	class WindowManager {
		// Object
		private:
			// Properties
			std::list<Window> windowList{};

		public:
			WindowManager() = default;
			WindowManager(const WindowManager& other) = delete;
			WindowManager(WindowManager&& other) noexcept = delete;
			~WindowManager() = default;

			// Operators | assignment
			WindowManager& operator=(const WindowManager& other) = delete;
			WindowManager& operator=(WindowManager&& other) noexcept = delete;

			// Functions
			Window& createWindow();
			Window& createWindow(int width, int height, const std::string& title);
			void destroyWindow(Window& window);
	};
}
