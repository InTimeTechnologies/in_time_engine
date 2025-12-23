#include "Joystick.h"

namespace it {
	void Joystick::feedAction(bool connected) {
		this->connected = connected;
	}
	void Joystick::feedAction(JoystickButtonCode joystickButtonCode, JoystickButton::Action action) {
		switch (joystickButtonCode) {
			case JoystickButtonCode::A:
				buttonA.feedAction(action);
				break;
			case JoystickButtonCode::B:
				buttonB.feedAction(action);
				break;
			case JoystickButtonCode::X:
				buttonX.feedAction(action);
				break;
			case JoystickButtonCode::Y:
				buttonY.feedAction(action);
				break;
			case JoystickButtonCode::LEFT_BUMPER:
				buttonLeftBumper.feedAction(action);
				break;
			case JoystickButtonCode::RIGHT_BUMPER:
				buttonRightBumper.feedAction(action);
				break;
			case JoystickButtonCode::BACK:
				buttonBack.feedAction(action);
				break;
			case JoystickButtonCode::START:
				buttonStart.feedAction(action);
				break;
			case JoystickButtonCode::LEFT_THUMB:
				buttonLeftThumb.feedAction(action);
				break;
			case JoystickButtonCode::RIGHT_THUMB:
				buttonRightThumb.feedAction(action);
				break;
			case JoystickButtonCode::DPAD_UP:
				buttonDpadUp.feedAction(action);
				break;
			case JoystickButtonCode::DPAD_RIGHT:
				buttonDpadRight.feedAction(action);
				break;
			case JoystickButtonCode::DPAD_DOWN:
				buttonDpadDown.feedAction(action);
				break;
			case JoystickButtonCode::DPAD_LEFT:
				buttonDpadLeft.feedAction(action);
				break;
			case JoystickButtonCode::UNKNOWN:
			default:
				break;
		}
	}
	void Joystick::feedAction(JoystickAxisCode joystickAxisCode, float value) {
		switch (joystickAxisCode) {
			case JoystickAxisCode::LEFT_X:
				axisLeftX.value = value;
				break;
			case JoystickAxisCode::LEFT_Y:
				axisLeftY.value = value;
				break;
			case JoystickAxisCode::RIGHT_X:
				axisRightX.value = value;
				break;
			case JoystickAxisCode::RIGHT_Y:
				axisRightY.value = value;
				break;
				case JoystickAxisCode::LEFT_TRIGGER:
				axisLeftTrigger.value = value;
				break;
			case JoystickAxisCode::RIGHT_TRIGGER:
				axisRightTrigger.value = value;
				break;
			default:
				break;
		}
	}
	void Joystick::reset() {
		buttonA.reset();
		buttonB.reset();
		buttonX.reset();
		buttonY.reset();

		buttonLeftBumper.reset();
		buttonRightBumper.reset();

		buttonBack.reset();
		buttonStart.reset();

		buttonLeftThumb.reset();
		buttonRightThumb.reset();

		buttonDpadUp.reset();
		buttonDpadRight.reset();
		buttonDpadLeft.reset();
		buttonDpadDown.reset();

		axisLeftX.reset();
		axisLeftY.reset();
		axisRightX.reset();
		axisRightY.reset();
		axisLeftTrigger.reset();
		axisRightTrigger.reset();
	}
	void Joystick::resetTransientState() {
		buttonA.resetTransientState();
		buttonB.resetTransientState();
		buttonX.resetTransientState();
		buttonY.resetTransientState();

		buttonLeftBumper.resetTransientState();
		buttonRightBumper.resetTransientState();

		buttonBack.resetTransientState();
		buttonStart.resetTransientState();

		buttonLeftThumb.resetTransientState();
		buttonRightThumb.resetTransientState();

		buttonDpadUp.resetTransientState();
		buttonDpadRight.resetTransientState();
		buttonDpadLeft.resetTransientState();
		buttonDpadDown.resetTransientState();
	}
}
