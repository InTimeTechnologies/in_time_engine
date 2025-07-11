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

#pragma once

// Dependencies | std
#include <array>

// Dependencies | OpenGLEngine
#include "JoystickButton.h"
#include "JoystickAxis.h"
#include "JoystickCode.h"

namespace glfw {
	struct Joystick {
		// Static

		// Properties
		static std::array<Joystick, 16> s_joysticks;

		// Functions
		static void s_resetJoystickButtons();
		static void s_updateJoysticks();

		// Callbacks
		static void s_joystickCallback(int joystickId, int connected);

		// Object

		// Properties
		bool connected = false;

		JoystickCode code = JoystickCode::UNKOWN;

		JoystickButton buttonA = JoystickButton(JoystickButtonCode::A, "A");
		JoystickButton buttonB = JoystickButton(JoystickButtonCode::B, "B");
		JoystickButton buttonX = JoystickButton(JoystickButtonCode::X, "X");
		JoystickButton buttonY = JoystickButton(JoystickButtonCode::Y, "Y");

		JoystickButton buttonLeftBumper = JoystickButton(JoystickButtonCode::LEFT_BUMPER, "left bumper");
		JoystickButton buttonRightBumper = JoystickButton(JoystickButtonCode::RIGHT_BUMPER, "right bumper");

		JoystickButton buttonBack = JoystickButton(JoystickButtonCode::BACK, "back");
		JoystickButton buttonStart = JoystickButton(JoystickButtonCode::START, "start");

		JoystickButton buttonLeftThumb = JoystickButton(JoystickButtonCode::LEFT_THUMB, "left thumb");
		JoystickButton buttonRightThumb = JoystickButton(JoystickButtonCode::RIGHT_THUMB, "right thumb");

		JoystickButton buttonDpadUp = JoystickButton(JoystickButtonCode::DPAD_UP, "dpad up");
		JoystickButton buttonDpadRight = JoystickButton(JoystickButtonCode::DPAD_RIGHT, "dpad right");
		JoystickButton buttonDpadLeft = JoystickButton(JoystickButtonCode::DPAD_LEFT, "dpad left");
		JoystickButton buttonDpadDown = JoystickButton(JoystickButtonCode::DPAD_DOWN, "dpad down");

		JoystickAxis axisLeftX = JoystickAxis(JoystickAxisCode::LEFT_X, "left x");
		JoystickAxis axisLeftY = JoystickAxis(JoystickAxisCode::LEFT_Y, "left y");
		JoystickAxis axisRightX = JoystickAxis(JoystickAxisCode::RIGHT_X, "right x");
		JoystickAxis axisRightY = JoystickAxis(JoystickAxisCode::RIGHT_Y, "right y");
		JoystickAxis axisLeftTrigger = JoystickAxis(JoystickAxisCode::LEFT_TRIGGER, "left trigger");
		JoystickAxis axisRightTrigger = JoystickAxis(JoystickAxisCode::RIGHT_TRIGGER, "right trigger");

		// Contructor / Destructor
		Joystick() {

		}
		Joystick(JoystickCode code) : code(code) {

		}
		~Joystick() {

		}
	};
}
