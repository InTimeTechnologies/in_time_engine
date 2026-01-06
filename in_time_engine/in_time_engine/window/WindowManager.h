#pragma once

// Dependencies | std
#include <list>
#include <string>

// Dependencies | in_time_engine | window
#include "backend/IWindowPlatformBackend.h"
#include "Window.h"

namespace it {
	class WindowManager {
		// Object
		private:
			// Properties
			std::list<Window> windowList{};

		public:
			// Properties
			IWindowPlatformBackend* iWindowPlatformBackend{ nullptr };

			// Constructor / Destructor
			WindowManager() = default;
			WindowManager(const WindowManager& other) = delete;
			WindowManager(WindowManager&& other) noexcept = delete;
			~WindowManager() = default;

			// Operators | assignment
			WindowManager& operator=(const WindowManager& other) = delete;
			WindowManager& operator=(WindowManager&& other) noexcept = delete;

			// Functions
			Window* createWindow();
			void destroyWindow(Window& window);
	};
}
