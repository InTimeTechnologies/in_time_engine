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
 * File: JoystickAxiscode.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  GLFW joystick axis codes stored in an enum with their corresponding
 *  integer values.
 *****************************************************************************/

#pragma once

// Dependencies | GLFW
#include <glfw/glfw3.h>

namespace glfw {
	enum class JoystickAxisCode {
		UNKNOWN = -1,
		LEFT_X = GLFW_GAMEPAD_AXIS_LEFT_X,
		LEFT_Y = GLFW_GAMEPAD_AXIS_LEFT_Y,
		RIGHT_X = GLFW_GAMEPAD_AXIS_RIGHT_X,
		RIGHT_Y = GLFW_GAMEPAD_AXIS_RIGHT_Y,
		LEFT_TRIGGER = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
		RIGHT_TRIGGER = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
	};
}
