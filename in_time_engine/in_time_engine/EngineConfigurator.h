#pragma once

// Dependencies | in_time_engine
#include "InTimeEngine.h"

namespace it {
	class EngineConfigurator {
		// Static
		public:
			// Properties
			static const bool S_GLFW_PRESENT;
			static const bool S_WIN32_PRESENT;
			static const bool S_QT_PRESENT;

			static const bool S_OPENGL_PRESENT;
			static const bool S_VULKAN_PRESENT;
			static const bool S_DIRECTX_PRESENT;

		// Object
		private:
			// Proprerties
			IPlatformBackend* glfwBackend{ nullptr };

		public:
			// Constructor / Destructor
			EngineConfigurator() = default;
			EngineConfigurator(const EngineConfigurator& other) = delete;
			EngineConfigurator(EngineConfigurator&& othe) noexcept = delete;
			~EngineConfigurator();

			// Operator | assignment
			EngineConfigurator& operator=(const EngineConfigurator& other) = delete;
			EngineConfigurator& operator=(EngineConfigurator&& other) noexcept = delete;

			// Functions
			bool linkEngineToGLFW(InTimeEngine& engine, bool useMouseKeyboard, bool useJoystick);
	};
}
