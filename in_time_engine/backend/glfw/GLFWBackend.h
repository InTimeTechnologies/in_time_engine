#pragma once

// Dependencies | glfw
#include <GLFW/glfw3.h>

// Dependencies | in_time_engine
#include <in_time_engine/IPlatformBackend.h>

// Dependencies | in_time_engine | input
#include <in_time_engine/input/mouse_keyboard/MouseKeyboardInput.h>
#include <in_time_engine/input/joystick/JoystickInput.h>

namespace it {

	// Functions
	GLFWwindow* toGLFWWindow(void* backendObjectHandle);

	class GLFWBackend : public IPlatformBackend {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static GLFWBackend* s_singleton;

		public:
			// Getters
			static GLFWBackend* s_getSingleton();

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
			GLFWBackend();
			GLFWBackend(const GLFWBackend& other) = delete;
			GLFWBackend(GLFWBackend&& other) noexcept = delete;
			~GLFWBackend();

			// Operators | assignment
			GLFWBackend& operator=(const GLFWBackend&) = delete;
			GLFWBackend& operator=(GLFWBackend&& other) noexcept = delete;

			// Functions
			bool init() override;
			bool deinit() override;
			bool isInit() const override;
			bool update() override;

			void linkToMouseKeyboardInput(MouseKeyboardInput* mouseKeyboardInput);
			void linkToJoystickInput(JoystickInput* joystickInput);
	};
}
