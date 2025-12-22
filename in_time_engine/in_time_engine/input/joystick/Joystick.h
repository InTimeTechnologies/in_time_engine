#pragma once

// Dependencies | std
#include <string>
#include <array>

// Dependencies | in_time_engine | input | joystick
#include "JoystickButtonCode.h"
#include "JoystickButton.h"
#include "JoystickAxis.h"
#include "JoystickCode.h"
#include "JoystickAxisCode.h"

namespace it {
	struct Joystick {
		// Properties
		JoystickCode code{ JoystickCode::UNKOWN };

		bool connected{ false };

		JoystickButton buttonA{ JoystickButtonCode::A, false, false, false, "A" };
		JoystickButton buttonB{ JoystickButtonCode::B, false, false, false, "B" };
		JoystickButton buttonX{ JoystickButtonCode::X, false, false, false, "X" };
		JoystickButton buttonY{ JoystickButtonCode::Y, false, false, false, "Y" };

		JoystickButton buttonLeftBumper{ JoystickButtonCode::LEFT_BUMPER, false, false, false, "left bumper" };
		JoystickButton buttonRightBumper{ JoystickButtonCode::RIGHT_BUMPER, false, false, false, "right bumper" };

		JoystickButton buttonBack{ JoystickButtonCode::BACK, false, false, false, "back" };
		JoystickButton buttonStart{ JoystickButtonCode::START, false, false, false, "start" };

		JoystickButton buttonLeftThumb{ JoystickButtonCode::LEFT_THUMB, false, false, false, "left thumb" };
		JoystickButton buttonRightThumb{ JoystickButtonCode::RIGHT_THUMB, false, false, false, "right thumb" };

		JoystickButton buttonDpadUp{ JoystickButtonCode::DPAD_UP, false, false, false, "dpad up" };
		JoystickButton buttonDpadRight{ JoystickButtonCode::DPAD_RIGHT, false, false, false, "dpad right" };
		JoystickButton buttonDpadLeft{ JoystickButtonCode::DPAD_LEFT, false, false, false, "dpad left" };
		JoystickButton buttonDpadDown{ JoystickButtonCode::DPAD_DOWN, false, false, false, "dpad down" };

		JoystickAxis axisLeftX{ JoystickAxis(JoystickAxisCode::LEFT_X, 0.0f, "left x") };
		JoystickAxis axisLeftY{ JoystickAxis(JoystickAxisCode::LEFT_Y, 0.0f, "left y") };
		JoystickAxis axisRightX{ JoystickAxis(JoystickAxisCode::RIGHT_X, 0.0f, "right x") };
		JoystickAxis axisRightY{ JoystickAxis(JoystickAxisCode::RIGHT_Y, 0.0f, "right y") };
		JoystickAxis axisLeftTrigger{ JoystickAxis(JoystickAxisCode::LEFT_TRIGGER, 0.0f, "left trigger") };
		JoystickAxis axisRightTrigger{ JoystickAxis(JoystickAxisCode::RIGHT_TRIGGER, 0.0f, "right trigger") };

		// Functions
		void feedAction(JoystickButtonCode joystickButtonCode, JoystickButton::Action action);
		void feedAction(JoystickAxisCode joystickAxisCode, float value);
		void reset();
		void resetTransientState();
	};
}
