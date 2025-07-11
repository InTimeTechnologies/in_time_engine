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
 * File: MouseButton.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  Sructure that represent the state of a single mouse button.
 *  - pressed
 *  - just pressed
 *  - just released
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <string>

// Dependencies | OpenGLEngine
#include "MouseButtonCode.h"

namespace glfw {
	struct MouseButton {
		// Properties
		MouseButtonCode buttonCode = MouseButtonCode::UNKNOWN;
		bool pressed = false;
		bool justPressed = false;
		bool justReleased = false;
		std::string description = "none";

		// Constructor / Destructor
		MouseButton() {

		}
		MouseButton(MouseButtonCode buttonCode, const std::string& description) : buttonCode(buttonCode), description(description) {

		}
		~MouseButton() {

		}
	};
}
