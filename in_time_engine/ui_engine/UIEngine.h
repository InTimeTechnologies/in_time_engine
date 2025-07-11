#pragma once

// Dependencies | imgui
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

// Dependencies | ui_engine
#include "UI.h"

namespace it {
	class UIEngine {
		// Static
		private:
			// Properties
			static UIEngine* s_singleton;

		public:
			// Getters
			static UIEngine* s_getSingleton();

		// Object
		public:
			// Constructor / Destructor
			UIEngine(GLFWwindow* window);
			~UIEngine();

			// Functions
			void render();
	};
}
