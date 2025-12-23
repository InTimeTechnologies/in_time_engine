#pragma once

// Dependencies | std
#include <array>

// Dependencies | in_time_engine | input | joystick
#include "Joystick.h"

namespace it {
	class JoystickInput {
		// Object
		private:
			// Properties
			std::array<Joystick, static_cast<size_t>(JoystickCode::COUNT)> joysticks{
				Joystick{ JoystickCode::UNKOWN },
				Joystick{ JoystickCode::CONTROLLER_0 },
				Joystick{ JoystickCode::CONTROLLER_1 },
				Joystick{ JoystickCode::CONTROLLER_2 },
				Joystick{ JoystickCode::CONTROLLER_3 },
				Joystick{ JoystickCode::CONTROLLER_4 },
				Joystick{ JoystickCode::CONTROLLER_5 },
				Joystick{ JoystickCode::CONTROLLER_6 },
				Joystick{ JoystickCode::CONTROLLER_7 },
				Joystick{ JoystickCode::CONTROLLER_8 },
				Joystick{ JoystickCode::CONTROLLER_9 },
				Joystick{ JoystickCode::CONTROLLER_10 },
				Joystick{ JoystickCode::CONTROLLER_11 },
				Joystick{ JoystickCode::CONTROLLER_12 },
				Joystick{ JoystickCode::CONTROLLER_13 },
				Joystick{ JoystickCode::CONTROLLER_14 },
				Joystick{ JoystickCode::CONTROLLER_15 }
			};

		public:
			// Getters
			const std::array<Joystick, static_cast<size_t>(JoystickCode::COUNT)>& getJoysticks() const;

			const Joystick& getJoystick(JoystickCode joystickCode) const;
			size_t getJoystickIndex(JoystickCode joystickCode) const;

			void feedAction(JoystickCode joystickCode, bool connected);
			void feedAction(JoystickCode joystickCode, JoystickButtonCode joystickButtoneCode, JoystickButton::Action action);
			void feedAction(JoystickCode joystickCode, JoystickAxisCode joystickAxisCode, float value);
			void reset();
			void resetTransientStates();
	};
}
