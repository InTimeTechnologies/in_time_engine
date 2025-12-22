#include "JoystickManager.h"

namespace it {
	// class JoystickManager

	// Object | public

	// Getters
	const std::array<Joystick, static_cast<size_t>(JoystickCode::COUNT)>& JoystickManager::getJoysticks() const {
		return joysticks;
	}

	const Joystick& JoystickManager::getJoystick(JoystickCode joystickCode) const {
		size_t i = getJoystickIndex(joystickCode);
		return joysticks[i];
	}
	size_t JoystickManager::getJoystickIndex(JoystickCode joystickCode) const {
		size_t i = static_cast<size_t>(joystickCode);
		size_t count = static_cast<size_t>(JoystickCode::COUNT);
		return i < count ? i : 0;
	}

	// Functions
	void JoystickManager::feedAction(JoystickCode joystickCode, JoystickButtonCode joystickButtonCode, JoystickButton::Action action) {
		size_t i = getJoystickIndex(joystickCode);
		joysticks[i].feedAction(joystickButtonCode, action);
	}
	void JoystickManager::feedAction(JoystickCode joystickCode, JoystickAxisCode joystickAxisCode, float value) {
		size_t i = getJoystickIndex(joystickCode);
		joysticks[i].feedAction(joystickAxisCode, value);
	}
	void JoystickManager::reset() {
		for (size_t i = 0; i < joysticks.size(); i++)
			joysticks[i].reset();
	}
	void JoystickManager::resetTransientStates() {
		for (size_t i = 0; i < joysticks.size(); i++)
			joysticks[i].resetTransientState();
	}
}