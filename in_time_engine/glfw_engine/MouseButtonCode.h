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
 *  GLFW mouse button codes stored in an enum with their corresponding
 *  integer values.
 *****************************************************************************/

#pragma once

// Dependencies | GLFW
#include <glfw/glfw3.h>

namespace glfw {
	enum class MouseButtonCode {
		UNKNOWN = -1,
		BUTTON_CODE_1 = GLFW_MOUSE_BUTTON_1,
		BUTTON_CODE_2 = GLFW_MOUSE_BUTTON_2,
		BUTTON_CODE_3 = GLFW_MOUSE_BUTTON_3,
		BUTTON_CODE_4 = GLFW_MOUSE_BUTTON_4,
		BUTTON_CODE_5 = GLFW_MOUSE_BUTTON_5,
		BUTTON_CODE_6 = GLFW_MOUSE_BUTTON_6,
		BUTTON_CODE_7 = GLFW_MOUSE_BUTTON_7,
		BUTTON_CODE_8 = GLFW_MOUSE_BUTTON_8
	};
}
