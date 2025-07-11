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
 * File: System.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  Serves as the interface to the GLFW code. Use this to init and deinit GLFW.
 *  This is the class that overrides IInputSystem.
 *  In Time Engine will call processInput and resetInput to manage mouse,
 *  keayboard and joystick input. Note that this is through glfwPollEvents.
 *  This causes to process all user interfaces events too.
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <functional>

// Dependencies | glfw_system
#include "WindowWrapper.h"

namespace glfw {
	class GLFWEngine {
		// Static
		private:
			// Properties
			static GLFWEngine* singleton;

		public:
			// Getters
			static GLFWEngine* getSingleton();

			// Callbacks
			static void s_errorCallback(int error_code, const char* description);
			static void s_monitorCallback(GLFWmonitor* monitor, int event);

		// Object
		public:
			// Callbacks
			std::function<void(int errorCode, const char* description)> errorCallback;
			std::function<void(GLFWmonitor* monitor, int event)> monitorCallback;

			// Constructor / Destructor
			GLFWEngine();
			~GLFWEngine();

			// Functions
			void processInput();
			void resetInput();
	};
}
