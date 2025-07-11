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
 *  Sructure that represent the state of a single mouse key.
 *  - pressed
 *  - just pressed
 *  - just released
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <string>

// Dependencies | OpenGLEngine
#include "KeyCode.h"

namespace glfw {
	struct Key {
		// Properties
		KeyCode keyCode = KeyCode::UNKNOWN;
		bool justPressed = false;
		bool repeat = false;
		bool justReleased = false;
		bool pressed = false;
		std::string description = "none";

		// Contructor / Destructor
		Key() {

		}
		Key(KeyCode keyCode, const std::string& description) : keyCode(keyCode), description(description) {

		}
		~Key() {

		}
	};
}
