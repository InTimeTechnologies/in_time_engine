/******************************************************************************
 * Copyright (c) 2024 Christopher Barrios Agosto. All Rights Reserved.
 *
 * Licensing Information:
 *  This software and associated documentation files (the "Software") may not
 *  be used, copied, modified, merged, published, distributed, sublicensed,
 *  or sold without the prior written permission of the copyright owner.
 *
 *  Unauthorized use of this file, via any medium, is strictly prohibited.
 *****************************************************************************/

/******************************************************************************
 * Project: In Time Engine
 * File: Joystick.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  Sructure that represent the state of every joystick button and axis.
 *   buttons:
 *   - pressed
 *   - just pressed
 *   - just released
 *   each axis:
 *   - value [-1, 1]
 *****************************************************************************/

#include "Joystick.h"

// struct GLFWJoystick

// Static | public

// Properties
std::array<glfw::Joystick, 16> glfw::Joystick::s_joysticks{
	Joystick(JoystickCode::CONTROLLER_0),
	Joystick(JoystickCode::CONTROLLER_1),
	Joystick(JoystickCode::CONTROLLER_2),
	Joystick(JoystickCode::CONTROLLER_3),
	Joystick(JoystickCode::CONTROLLER_4),
	Joystick(JoystickCode::CONTROLLER_5),
	Joystick(JoystickCode::CONTROLLER_6),
	Joystick(JoystickCode::CONTROLLER_7),
	Joystick(JoystickCode::CONTROLLER_8),
	Joystick(JoystickCode::CONTROLLER_9),
	Joystick(JoystickCode::CONTROLLER_10),
	Joystick(JoystickCode::CONTROLLER_11),
	Joystick(JoystickCode::CONTROLLER_12),
	Joystick(JoystickCode::CONTROLLER_13),
	Joystick(JoystickCode::CONTROLLER_14),
	Joystick(JoystickCode::CONTROLLER_15)
};

// Functions
void glfw::Joystick::s_resetJoystickButtons() {
	for (int joystickIndex = 0; joystickIndex < s_joysticks.size(); joystickIndex++) {
		if (!s_joysticks[joystickIndex].connected)
			continue;

		s_joysticks[joystickIndex].buttonA.justPressed = false;
		s_joysticks[joystickIndex].buttonA.justReleased = false;
		s_joysticks[joystickIndex].buttonB.justPressed = false;
		s_joysticks[joystickIndex].buttonB.justReleased = false;
		s_joysticks[joystickIndex].buttonX.justPressed = false;
		s_joysticks[joystickIndex].buttonX.justReleased = false;
		s_joysticks[joystickIndex].buttonY.justPressed = false;
		s_joysticks[joystickIndex].buttonY.justReleased = false;

		s_joysticks[joystickIndex].buttonLeftBumper.justPressed = false;
		s_joysticks[joystickIndex].buttonLeftBumper.justReleased = false;
		s_joysticks[joystickIndex].buttonRightBumper.justPressed = false;
		s_joysticks[joystickIndex].buttonRightBumper.justReleased = false;

		s_joysticks[joystickIndex].buttonBack.justPressed = false;
		s_joysticks[joystickIndex].buttonBack.justReleased = false;
		s_joysticks[joystickIndex].buttonStart.justPressed = false;
		s_joysticks[joystickIndex].buttonStart.justReleased = false;

		s_joysticks[joystickIndex].buttonLeftThumb.justPressed = false;
		s_joysticks[joystickIndex].buttonLeftThumb.justReleased = false;
		s_joysticks[joystickIndex].buttonRightThumb.justPressed = false;
		s_joysticks[joystickIndex].buttonRightThumb.justReleased = false;

		s_joysticks[joystickIndex].buttonDpadDown.justPressed = false;
		s_joysticks[joystickIndex].buttonDpadDown.justReleased = false;
		s_joysticks[joystickIndex].buttonDpadUp.justPressed = false;
		s_joysticks[joystickIndex].buttonDpadUp.justReleased = false;
		s_joysticks[joystickIndex].buttonDpadLeft.justPressed = false;
		s_joysticks[joystickIndex].buttonDpadLeft.justReleased = false;
		s_joysticks[joystickIndex].buttonDpadRight.justPressed = false;
		s_joysticks[joystickIndex].buttonDpadRight.justReleased = false;
	}
}
void glfw::Joystick::s_updateJoysticks() {
	for (int controllerIndex = 0; controllerIndex < 12; controllerIndex++) {
		bool controllerConnected = glfwJoystickPresent(controllerIndex);
		s_joysticks[controllerIndex].connected = controllerConnected;
		if (controllerConnected) {
			// Get button values for current controller
			int buttonCount = 0;
			const unsigned char* buttonValues = glfwGetJoystickButtons((int)s_joysticks[controllerIndex].code, &buttonCount);
			if (buttonValues == nullptr)
				continue;
			for (int buttonIndex = 0; buttonIndex <= buttonCount; buttonIndex++) {
				switch ((JoystickButtonCode)buttonIndex) {
				case JoystickButtonCode::A:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonA;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonA.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::B:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonB;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonB.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::X:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonX;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonX.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::Y:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonY;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonY.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::LEFT_BUMPER:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonLeftBumper;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonLeftBumper.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::RIGHT_BUMPER:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonRightBumper;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonRightBumper.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::BACK:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonBack;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonBack.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::START:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonStart;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonStart.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::RIGHT_THUMB:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonRightThumb;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonRightThumb.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::LEFT_THUMB:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonLeftThumb;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonLeftThumb.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::DPAD_UP:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonDpadUp;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonDpadUp.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::DPAD_RIGHT:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonDpadRight;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonDpadRight.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::DPAD_DOWN:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonDpadDown;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonDpadDown.pressed)
						joystickButton.justReleased = true;
					joystickButton.pressed = pressed;
				}
				break;
				case JoystickButtonCode::DPAD_LEFT:
				{
					JoystickButton& joystickButton = s_joysticks[controllerIndex].buttonDpadLeft;
					bool pressed = buttonValues[buttonIndex] == GLFW_PRESS ? true : false;
					if (pressed && !joystickButton.pressed)
						joystickButton.justPressed = true;
					else if (!pressed && s_joysticks[controllerIndex].buttonDpadLeft.pressed)
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
			const float* axisValues = glfwGetJoystickAxes((int)s_joysticks[controllerIndex].code, &axisCount);
			for (int axisIndex = 0; axisIndex < axisCount; axisIndex++) {
				switch ((JoystickAxisCode)axisIndex) {
				case JoystickAxisCode::LEFT_X:
					s_joysticks[controllerIndex].axisLeftX.value = axisValues[axisIndex];
					break;
				case JoystickAxisCode::LEFT_Y:
					s_joysticks[controllerIndex].axisLeftY.value = axisValues[axisIndex];
					break;
				case JoystickAxisCode::RIGHT_X:
					s_joysticks[controllerIndex].axisRightX.value = axisValues[axisIndex];
					break;
				case JoystickAxisCode::RIGHT_Y:
					s_joysticks[controllerIndex].axisRightY.value = axisValues[axisIndex];
					break;
				case JoystickAxisCode::LEFT_TRIGGER:
					s_joysticks[controllerIndex].axisLeftTrigger.value = axisValues[axisIndex];
					break;
				case JoystickAxisCode::RIGHT_TRIGGER:
					s_joysticks[controllerIndex].axisRightTrigger.value = axisValues[axisIndex];
					break;
				}
			}
		}
	}
}

// Callbacks
void glfw::Joystick::s_joystickCallback(int joystickId, int connected) {
	
}
