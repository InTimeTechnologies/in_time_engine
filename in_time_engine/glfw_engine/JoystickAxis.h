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
 * File: JoystickAxis.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  Sructure that represent the values of the joystick axis.
 *  - value [-1, 1]
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <string>

// Dependencies | OpenGLEngine
#include "JoystickAxisCode.h"

namespace glfw {
	struct JoystickAxis {
		JoystickAxisCode axisCode = JoystickAxisCode::UNKNOWN;
		float value = 0.0f;
		std::string description = "none";

		JoystickAxis() {

		}
		JoystickAxis(JoystickAxisCode axisCode, const std::string& description) : axisCode(axisCode), description(description) {

		}
		~JoystickAxis() {

		}
	};
}
