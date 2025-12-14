#include "GLFWJoystickManager.h"

namespace glfw {
	// struct JoystickManager

	// Functions
	void JoystickManager::reset() {
		for (int joystickIndex = 0; joystickIndex < joysticks.size(); joystickIndex++) {
			if (!joysticks[joystickIndex].connected)
				continue;

			joysticks[joystickIndex].buttonA.justPressed = false;
			joysticks[joystickIndex].buttonA.justReleased = false;
			joysticks[joystickIndex].buttonB.justPressed = false;
			joysticks[joystickIndex].buttonB.justReleased = false;
			joysticks[joystickIndex].buttonX.justPressed = false;
			joysticks[joystickIndex].buttonX.justReleased = false;
			joysticks[joystickIndex].buttonY.justPressed = false;
			joysticks[joystickIndex].buttonY.justReleased = false;

			joysticks[joystickIndex].buttonLeftBumper.justPressed = false;
			joysticks[joystickIndex].buttonLeftBumper.justReleased = false;
			joysticks[joystickIndex].buttonRightBumper.justPressed = false;
			joysticks[joystickIndex].buttonRightBumper.justReleased = false;

			joysticks[joystickIndex].buttonBack.justPressed = false;
			joysticks[joystickIndex].buttonBack.justReleased = false;
			joysticks[joystickIndex].buttonStart.justPressed = false;
			joysticks[joystickIndex].buttonStart.justReleased = false;

			joysticks[joystickIndex].buttonLeftThumb.justPressed = false;
			joysticks[joystickIndex].buttonLeftThumb.justReleased = false;
			joysticks[joystickIndex].buttonRightThumb.justPressed = false;
			joysticks[joystickIndex].buttonRightThumb.justReleased = false;

			joysticks[joystickIndex].buttonDpadDown.justPressed = false;
			joysticks[joystickIndex].buttonDpadDown.justReleased = false;
			joysticks[joystickIndex].buttonDpadUp.justPressed = false;
			joysticks[joystickIndex].buttonDpadUp.justReleased = false;
			joysticks[joystickIndex].buttonDpadLeft.justPressed = false;
			joysticks[joystickIndex].buttonDpadLeft.justReleased = false;
			joysticks[joystickIndex].buttonDpadRight.justPressed = false;
			joysticks[joystickIndex].buttonDpadRight.justReleased = false;
		}
	}
	void JoystickManager::update() {
		for (int controllerIndex = 0; controllerIndex < 12; controllerIndex++) {
			bool controllerConnected = glfwJoystickPresent(controllerIndex);
			joysticks[controllerIndex].connected = controllerConnected;
			if (controllerConnected) {
				// Get button values for current controller
				int buttonCount = 0;
				const unsigned char* buttonValues = glfwGetJoystickButtons((int)joysticks[controllerIndex].code, &buttonCount);
				if (buttonValues == nullptr)
					continue;
				for (int buttonIndex = 0; buttonIndex <= buttonCount; buttonIndex++) {
					switch ((JoystickButtonCode)buttonIndex) {
					case JoystickButtonCode::A:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonA;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonA.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::B:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonB;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonB.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::X:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonX;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonX.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::Y:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonY;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonY.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::LEFT_BUMPER:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonLeftBumper;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonLeftBumper.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::RIGHT_BUMPER:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonRightBumper;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonRightBumper.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::BACK:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonBack;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonBack.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::START:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonStart;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonStart.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::RIGHT_THUMB:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonRightThumb;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonRightThumb.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::LEFT_THUMB:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonLeftThumb;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonLeftThumb.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::DPAD_UP:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonDpadUp;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonDpadUp.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::DPAD_RIGHT:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonDpadRight;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonDpadRight.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::DPAD_DOWN:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonDpadDown;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonDpadDown.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					case JoystickButtonCode::DPAD_LEFT:
					{
						JoystickButton& joystickButton = joysticks[controllerIndex].buttonDpadLeft;
						bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
						if (pressed && !joystickButton.pressed)
							joystickButton.justPressed = true;
						else if (!pressed && joysticks[controllerIndex].buttonDpadLeft.pressed)
							joystickButton.justReleased = true;
						joystickButton.pressed = pressed;
					}
					break;
					default:
						break;
					}
				}

				// Get the thumb axis values for current controller
				int axisCount = 0;
				const float* axisValues = glfwGetJoystickAxes((int)joysticks[controllerIndex].code, &axisCount);
				for (int axisIndex = 0; axisIndex < axisCount; axisIndex++) {
					switch ((JoystickAxisCode)axisIndex) {
					case JoystickAxisCode::LEFT_X:
						joysticks[controllerIndex].axisLeftX.value = axisValues[axisIndex];
						break;
					case JoystickAxisCode::LEFT_Y:
						joysticks[controllerIndex].axisLeftY.value = axisValues[axisIndex];
						break;
					case JoystickAxisCode::RIGHT_X:
						joysticks[controllerIndex].axisRightX.value = axisValues[axisIndex];
						break;
					case JoystickAxisCode::RIGHT_Y:
						joysticks[controllerIndex].axisRightY.value = axisValues[axisIndex];
						break;
					case JoystickAxisCode::LEFT_TRIGGER:
						joysticks[controllerIndex].axisLeftTrigger.value = axisValues[axisIndex];
						break;
					case JoystickAxisCode::RIGHT_TRIGGER:
						joysticks[controllerIndex].axisRightTrigger.value = axisValues[axisIndex];
						break;
					}
				}
			}
		}
	}
}