#pragma once

// Dependencies | InTimeEngine
#include <in_time_engine/InTimeEngine.h>
#include <glfw_engine/GLFWEngine.h>

// Dependencies | std
#include <vector>
#include <functional>
#include <iostream>

namespace it {
	class KeyControl : public UpdateEvent {
		public:
			// Properties
			std::vector<glfw::KeyCode> keysToMatch;
			std::function<void()> function;

			// Constructor / Destructor
			KeyControl() = default;
			~KeyControl() = default;

			// Events
			void onPreUpdate() override {
				if (!static_cast<bool>(function))
					return;

				glfw::Engine* glfwEngine{ glfw::Engine::getSingleton() };
				if (glfwEngine == nullptr)
					return;

				std::list<glfw::Window>& windows = glfwEngine->windowManager.windows;
				if (windows.size() == 0)
					return;

				glfw::Input& input = windows.front().input;
				for (glfw::KeyCode& keyCode : keysToMatch)
					if (!input.getKey(keyCode).pressed)
						return;

				function();
			}
			void onPostUpdate() override {
				// Ignored
			}
	};
}
