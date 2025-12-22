#pragma once

// Dependencies | std
#include <string>

// Dependencies | in_time_engine | input | mouse_keyboard
#include "KeyCode.h"

namespace it {
	struct Key {
		// Enums
		enum class Action : size_t {
			UNKNOWN,
			PRESSED,
			RELEASED,
			REPEAT
		};

		// Properties
		KeyCode keyCode{ KeyCode::UNKNOWN };
		bool justPressed{ false };
		bool repeat{ false };
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
