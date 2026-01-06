#pragma once

// Dependencies | glfw
#include <GLFW/glfw3.h>

// Dependencies | in_time_engine
#include <in_time_engine/IPlatformBackend.h>

// Dependencies | in_time_engine | input
#include <in_time_engine/input/mouse_keyboard/MouseKeyboardInput.h>
#include <in_time_engine/input/joystick/JoystickInput.h>

// Dependencies | in_time_engine | window | backend
#include <in_time_engine/window/backend/IWindowPlatformBackend.h>

// Dependencies | in_time_engine | backend | glfw
#include "GLFWWindowBackend.h"

namespace it {
	// Functions
	GLFWwindow* toGLFWWindow(void* backendObjectHandle);

	class GLFWPlatformBackend : public IPlatformBackend, public IWindowPlatformBackend {
		// Friends
		friend class EngineConfigurator;
		friend class GLFWWindowBackend;

		// Static
		private:
			// Properties
			static GLFWPlatformBackend* s_singleton;

		public:
			// Getters
			static GLFWPlatformBackend* s_getSingleton();

			// Functions
			static KeyCode s_ToKeyCode(int glfwKey);
			static Key::Action s_ToKeyAction(int glfwAction);
			static MouseButtonCode s_toMouseButtonCode(int glfwMouseButton);
			static MouseButton::Action s_toMouseButtonAction(int glfwAction);

			// Callbacks
			static void s_keyCallback(GLFWwindow* glfwWindow, int glfwKey, int glfwScanCode, int glfwAction, int glfwMods);
			static void s_mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
			
		// Object
		private:
			// Properties
			MouseKeyboardInput* mouseKeyboardInput{ nullptr };
			JoystickInput* joystickInput{ nullptr };

		public:
			GLFWPlatformBackend();
			GLFWPlatformBackend(const GLFWPlatformBackend& other) = delete;
			GLFWPlatformBackend(GLFWPlatformBackend&& other) noexcept = delete;
			~GLFWPlatformBackend();

			// Operators | assignment
			GLFWPlatformBackend& operator=(const GLFWPlatformBackend&) = delete;
			GLFWPlatformBackend& operator=(GLFWPlatformBackend&& other) noexcept = delete;

			// Functions
			void linkToMouseKeyboardInput(MouseKeyboardInput* mouseKeyboardInput);
			void linkToJoystickInput(JoystickInput* joystickInput);

			// Functions | IPlatformBackend
			bool init() override;
			bool deinit() override;
			bool isInit() const override;
			bool update() override;

			// Functions | IWindowPlatformBackend
			IWindowBackend* createWindowBackend(Window& window) override;
			void destroyWindowBackend(IWindowBackend* iWindowBackend) override;

	};
}
