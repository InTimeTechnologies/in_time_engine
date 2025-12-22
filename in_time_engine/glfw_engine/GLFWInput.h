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
 *  Sructure that represent the state of each keyboard key and mouse button:
 *   - pressed
 *   - just pressed
 *   - just released
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <forward_list>
#include <array>

// Dependencies | GLFWInterface
#include "GLFWKeyCode.h"
#include "GLFWKey.h"
#include "GLFWMouseButtonCode.h"
#include "GLFWMouseButton.h"

namespace glfw {
	class Input {
		// Friends
		friend class Window;

		// Object
		private:
			// Properties
			std::forward_list<Key*> keysToReset = std::forward_list<Key*>();
			std::forward_list<MouseButton*> mouseButtonsToReset = std::forward_list<MouseButton*>();

		public:
			// Properties
			std::array<Key, 121> keys = std::array<Key, 121>();
			std::array<MouseButton, 8> mouseButtons = std::array<MouseButton, 8>();

		public:
			// Constructor / Destructor
			Input();
			~Input() = default;

			// Getters
			Key getKey(KeyCode keyCode);
			int getKeyIndex(KeyCode keyCode);

			MouseButton getMouseButton(MouseButtonCode mouseButtonCode);
			int getMouseButtonIndex(MouseButtonCode mouseButtonCode);

			// Functions | IInput
			void reset();
	};
}
