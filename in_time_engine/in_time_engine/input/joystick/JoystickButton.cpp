#include "JoystickButton.h"

namespace it {
	// struct JoysticButton

	// Functions
	bool JoystickButton::inTransientState() const {
		return justPressed || justReleased;
	}
	void JoystickButton::feedAction(Action action) {
		switch (action) {
		case Action::PRESSED:
			justPressed = true;
			pressed = true;
			break;
		case Action::RELEASED:
			justReleased = true;
			pressed = false;
			break;
		}
	}
	void JoystickButton::reset() {
		justPressed = false;
		justReleased = false;
		pressed = false;
	}
	void JoystickButton::resetTransientState() {
		justPressed = false;
		justReleased = false;
	}
	void JoystickButton::resetJustPressed() {
		justPressed = false;
	}
	void JoystickButton::resetJustReleased() {
		justReleased = false;
	}
}