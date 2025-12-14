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
 * File: MouseButtonCode.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  GLFW joystic codes stored in an enum with their corresponding
 *  integer values.
 *****************************************************************************/

#pragma once

// Dependencies | GLFW
#include <glfw/glfw3.h>

namespace glfw {
	enum class JoystickCode {
		UNKOWN = -1,
		CONTROLLER_0 = GLFW_JOYSTICK_1,
		CONTROLLER_1 = GLFW_JOYSTICK_2,
		CONTROLLER_2 = GLFW_JOYSTICK_3,
		CONTROLLER_3 = GLFW_JOYSTICK_4,
		CONTROLLER_4 = GLFW_JOYSTICK_5,
		CONTROLLER_5 = GLFW_JOYSTICK_6,
		CONTROLLER_6 = GLFW_JOYSTICK_7,
		CONTROLLER_7 = GLFW_JOYSTICK_8,
		CONTROLLER_8 = GLFW_JOYSTICK_9,
		CONTROLLER_9 = GLFW_JOYSTICK_10,
		CONTROLLER_10 = GLFW_JOYSTICK_11,
		CONTROLLER_11 = GLFW_JOYSTICK_12,
		CONTROLLER_12 = GLFW_JOYSTICK_13,
		CONTROLLER_13 = GLFW_JOYSTICK_14,
		CONTROLLER_14 = GLFW_JOYSTICK_15,
		CONTROLLER_15 = GLFW_JOYSTICK_16,
	};
}