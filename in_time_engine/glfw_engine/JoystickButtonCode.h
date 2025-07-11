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
 * File: JoystickButtonCode.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  GLFW joystick button codes stored in an enum with their corresponding
 *  integer values.
 *****************************************************************************/

#pragma once

// Dependencies | GLFW
#include <glfw/glfw3.h>

namespace glfw {
	enum class JoystickButtonCode {
		UNKNOWN = -1,
		A = GLFW_GAMEPAD_BUTTON_A,
		B = GLFW_GAMEPAD_BUTTON_B,
		X = GLFW_GAMEPAD_BUTTON_X,
		Y = GLFW_GAMEPAD_BUTTON_Y,
		LEFT_BUMPER = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
		RIGHT_BUMPER = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
		BACK = GLFW_GAMEPAD_BUTTON_BACK,
		START = GLFW_GAMEPAD_BUTTON_START,
		//GUIDE =			GLFW_GAMEPAD_BUTTON_GUIDE,
		LEFT_THUMB = GLFW_GAMEPAD_BUTTON_LEFT_THUMB - 1,
		RIGHT_THUMB = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB - 1,
		DPAD_UP = GLFW_GAMEPAD_BUTTON_DPAD_UP - 1,
		DPAD_RIGHT = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT - 1,
		DPAD_DOWN = GLFW_GAMEPAD_BUTTON_DPAD_DOWN - 1,
		DPAD_LEFT = GLFW_GAMEPAD_BUTTON_DPAD_LEFT - 1
	};
}
