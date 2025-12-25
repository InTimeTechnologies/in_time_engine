#include "EngineConfigurator.h"

// Dependencies | in_time_engine | backend
#if defined(GLFW)
#include "backend/glfw/GLFWBackend.h"
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

	// Object | public

	// Constructor / Destructor
	EngineConfigurator::~EngineConfigurator() {
		if (glfwBackend != nullptr) {
			delete glfwBackend;
			glfwBackend = nullptr;
		}
	}

	// Functions
	bool EngineConfigurator::linkEngineToGLFW(InTimeEngine& engine, bool useMouseKeyboard, bool useJoystick) {
#if defined(GLFW)
		GLFWBackend* backend = new GLFWBackend();
		bool glfwInitiatedSuccessfully = backend->init();
		assert(glfwInitiatedSuccessfully && "Failed to initiate glfw.");
		if (!glfwInitiatedSuccessfully)
			return false;

		backend->joystickInput = &engine.joystickInput;
		backend->mouseKeyboardInput = &engine.mouseKeyboardInput;
		engine.inputEventBackend = backend;

		this->glfwBackend = backend;

		return true;
#else
		return false;
#endif
	}
}
