#pragma once

// Dependencies | std
#include <string>

// Dependencies | in_time_engine | input | joystick
#include "JoystickButtonCode.h"

namespace it {
	struct JoystickButton {
		// Enums
		enum class Action : size_t {
			UNKNOWN,
			PRESSED,
			RELEASED
		};
		
		// Properties
		JoystickButtonCode buttonCode{ JoystickButtonCode::UNKNOWN };
		bool justPressed{ false };
		bool justReleased{ false };
		bool pressed{ false };
		std::string description{};

		// Functions
		bool inTransientState() const;
		void feedAction(Action action);
		void reset();
		void resetTransientState();
		void resetJustPressed();
		void resetJustReleased();
	};
}
