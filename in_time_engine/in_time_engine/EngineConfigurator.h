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

			// Functions
			static bool s_linkEngineToGLFW(InTimeEngine& engine, bool useWindowBackend, bool forwardMouseKeyboardInput, bool forwardJoystickInput);
	};
}
