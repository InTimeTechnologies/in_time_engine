#include "JoystickInput.h"

namespace it {
	// class JoystickInput

	// Object | public

	// Getters
	const std::array<Joystick, static_cast<size_t>(JoystickCode::COUNT)>& JoystickInput::getJoysticks() const {
		return joysticks;
	}

	const Joystick& JoystickInput::getJoystick(JoystickCode joystickCode) const {
		size_t i = getJoystickIndex(joystickCode);
		return joysticks[i];
	}
	size_t JoystickInput::getJoystickIndex(JoystickCode joystickCode) const {
		size_t i = static_cast<size_t>(joystickCode);
		size_t count = static_cast<size_t>(JoystickCode::COUNT);
		return i < count ? i : 0;
	}

	// Functions
	void JoystickInput::feedAction(JoystickCode joystickCode, bool connected) {
		size_t i = getJoystickIndex(joystickCode);
		joysticks[i].connected = connected;
	}
	void JoystickInput::feedAction(JoystickCode joystickCode, JoystickButtonCode joystickButtonCode, JoystickButton::Action action) {
		size_t i = getJoystickIndex(joystickCode);
		joysticks[i].feedAction(joystickButtonCode, action);
	}
	void JoystickInput::feedAction(JoystickCode joystickCode, JoystickAxisCode joystickAxisCode, float value) {
		size_t i = getJoystickIndex(joystickCode);
		joysticks[i].feedAction(joystickAxisCode, value);
	}
	void JoystickInput::reset() {
		for (size_t i = 0; i < joysticks.size(); i++)
			joysticks[i].reset();
	}
	void JoystickInput::resetTransientStates() {
		for (size_t i = 0; i < joysticks.size(); i++)
			joysticks[i].resetTransientState();
	}
}