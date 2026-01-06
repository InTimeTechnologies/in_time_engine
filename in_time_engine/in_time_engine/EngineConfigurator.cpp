#include "EngineConfigurator.h"

// Dependencies | std
#include <cassert>

// Dependencies | in_time_engine | backend
#if defined(GLFW)
#include "backend/glfw/GLFWPlatformBackend.h"
#endif

namespace it {
	// class EngineConfigurator

	// Static | public

	// Properties | platforms
#if defined(GLFW)
	const bool S_GLFW_PRESENT = true;
#else
	const bool S_GLFW_PRESENT = false;
#endif
#if defined(WIN32)
	const bool S_WIN32_PRESENT = true;
#else
	const bool S_WIN32_PRESENT = false;
#endif
#if defined(QT)
	const bool S_QT_PRESENT = true;
#else
	const bool S_QT_PRESENT = false;
#endif

	// Properties | graphics API
#if defined(OPENGL)
	const bool S_OPENGL_PRESENT = true;
#else
	const bool S_OPENGL_PRESENT = false;
#endif
#if defined(VULKAN)
	const bool S_VULKAN_PRESENT = true;
#else
	const bool S_VULKAN_PRESENT = false;
#endif
#if defined(DIRECTX)
	const bool S_DIRECTX_PRESENT = true;
#else
	const bool S_DIRECTX_PRESENT = false;
#endif

	// Functions
	bool EngineConfigurator::s_linkEngineToGLFW(InTimeEngine& engine, bool useWindowBackend, bool forwardMouseKeyboardInput, bool forwardJoystickInput) {
#if defined(GLFW)
		GLFWPlatformBackend* backend = new GLFWPlatformBackend();
		bool glfwInitiatedSuccessfully = backend->init();
		assert(glfwInitiatedSuccessfully && "Failed to initiate glfw.");
		if (!glfwInitiatedSuccessfully)
			return false;

		engine.inputEventBackend = backend;

		if (useWindowBackend)
			engine.windowManager.iWindowPlatformBackend = backend;
		if (forwardMouseKeyboardInput)
			backend->joystickInput = &engine.joystickInput;
		if (forwardJoystickInput)
			backend->mouseKeyboardInput = &engine.mouseKeyboardInput;

		return true;
#else
		return false;
#endif
	}
}
