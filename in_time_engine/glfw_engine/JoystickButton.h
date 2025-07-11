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
 * File: JoystickButton.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  Sructure that represent the state of a single joystick button.
 *  - pressed
 *  - just pressed
 *  - just released
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <string>

// Dependencies | OpenGLEngine
#include "JoystickButtonCode.h"

namespace glfw {
	struct JoystickButton {
		JoystickButtonCode buttonCode = JoystickButtonCode::UNKNOWN;
		bool justPressed = false;
		bool justReleased = false;
		bool pressed = false;
		std::string description = "none";

		JoystickButton(JoystickButtonCode buttonCode, const std::string& description) : buttonCode(buttonCode), description(description) {

		}
		~JoystickButton() {

		}
	};
}
