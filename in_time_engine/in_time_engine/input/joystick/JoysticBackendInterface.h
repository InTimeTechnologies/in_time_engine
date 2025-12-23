#pragma once

// Dependencies | in_time_engine | input | joystick
#include "JoystickManager.h"

namespace it {
	class JoystickBackendInterface {
		// Object
		public:
			// Properties
			JoystickManager* joystickManager{ nullptr };

			// Functions
			virtual void feedAction(bool connected) = 0;
			virtual void feedAction(JoystickButtonCode joystickButtonCode, JoystickButton::Action action) = 0;
			virtual void feedAction(JoystickAxisCode joystickAxisCode, float value) = 0;
	};
}
