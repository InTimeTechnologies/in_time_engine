#pragma once

// Dependencies | std
#include <array>

// Dependencies | glfw_engine
#include "GLFWJoystick.h"

namespace glfw {
	struct JoystickManager {
		// Object

		// Properties
		std::array<Joystick, 16> joysticks{
			Joystick(JoystickCode::CONTROLLER_0),
			Joystick(JoystickCode::CONTROLLER_1),
			Joystick(JoystickCode::CONTROLLER_2),
			Joystick(JoystickCode::CONTROLLER_3),
			Joystick(JoystickCode::CONTROLLER_4),
			Joystick(JoystickCode::CONTROLLER_5),
			Joystick(JoystickCode::CONTROLLER_6),
			Joystick(JoystickCode::CONTROLLER_7),
			Joystick(JoystickCode::CONTROLLER_8),
			Joystick(JoystickCode::CONTROLLER_9),
			Joystick(JoystickCode::CONTROLLER_10),
			Joystick(JoystickCode::CONTROLLER_11),
			Joystick(JoystickCode::CONTROLLER_12),
			Joystick(JoystickCode::CONTROLLER_13),
			Joystick(JoystickCode::CONTROLLER_14),
			Joystick(JoystickCode::CONTROLLER_15)
		};

		// Functions
		void reset();
		void update();
	};
}