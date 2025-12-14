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
 * File: System.cpp
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

#include "GLFWEngine.h"

// Dependencies | std
#include <cassert>

// class Engine

// Static | private

// Properties
glfw::Engine* glfw::Engine::singleton = nullptr;

// Static | public

// Getters
glfw::Engine* glfw::Engine::getSingleton() {
	return singleton;
}

// Callbacks
void glfw::Engine::s_errorCallback(int error_code, const char* description) {
	if (singleton == nullptr || !static_cast<bool>(singleton->errorCallback))
		return;
	singleton->errorCallback(error_code, description);
}
void glfw::Engine::s_monitorCallback(GLFWmonitor* monitor, int event) {
	if (singleton == nullptr || !static_cast<bool>(singleton->monitorCallback))
		return;
	singleton->monitorCallback(monitor, event);
}

// Object | public

// Constructor / Destructor
glfw::Engine::Engine(bool createWindow) {
	if (singleton == nullptr) {
		int initSuccess = glfwInit();
		assert(initSuccess && "glfw did not initiated.");
		
		glfwSetErrorCallback(s_errorCallback);
		glfwSetMonitorCallback(s_monitorCallback);

		singleton = this;
	}

	if (createWindow)
		windowManager.createWindow();
}
glfw::Engine::~Engine() {
	if (singleton == this) {
		glfwTerminate();
		singleton = nullptr;
	}
}

// Functions
void glfw::Engine::processInput() {
	// Process window events, joystick, mouse and keyboard input
	glfwPollEvents();

	// Further process joystick input
	joystickManager.update();
}
void glfw::Engine::resetInput() {
	for (Window& window : windowManager.windows)
		window.input.reset();

	joystickManager.reset();
}
