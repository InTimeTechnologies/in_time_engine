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
 * File: Window.cpp
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  Wrapper class around GLFW window pointer.
 *  Each window has its own Input object (mouse and keyboard).
 *****************************************************************************/

#include "WindowWrapper.h"

// Dependencies | std
#include <cassert>

// class Window

// Static | private

// Properties
std::list<glfw::WindowWrapper*> glfw::WindowWrapper::windowList = std::list<glfw::WindowWrapper*>();

// Static | public

// Properties
int glfw::WindowWrapper::defaultWidth = 800;
int glfw::WindowWrapper::defaultHeight = 600;
std::string glfw::WindowWrapper::s_defaultName = "GLFW Window";

// Getters
std::list<glfw::WindowWrapper*> glfw::WindowWrapper::getWindowList() {
	return windowList;
}

// Callbacks
void glfw::WindowWrapper::s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);
	if (glfwWindow == nullptr)
		return;

	int keyIndex = glfwWindow->input.getKeyIndex((KeyCode)key);

	if (action == GLFW_PRESS) {
		glfwWindow->input.keys[keyIndex].justPressed = true;
		glfwWindow->input.keys[keyIndex].pressed = true;
	}
	if (action == GLFW_REPEAT) {
		glfwWindow->input.keys[keyIndex].repeat = true;
	}
	if (action == GLFW_RELEASE) {
		glfwWindow->input.keys[keyIndex].justReleased = true;
		glfwWindow->input.keys[keyIndex].pressed = false;
	}

	glfwWindow->input.keysToReset.push_front(&glfwWindow->input.keys[keyIndex]);

	#if defined(IMGUI)
	ImGuiIO& io = ImGui::GetIO();
	if (action == GLFW_PRESS)
		io.KeysData[key].Down = true;
	else if (action == GLFW_RELEASE)
		io.KeysData[key].Down = false;

	io.KeyCtrl = (mods & GLFW_MOD_CONTROL) != 0;
	io.KeyShift = (mods & GLFW_MOD_SHIFT) != 0;
	io.KeyAlt = (mods & GLFW_MOD_ALT) != 0;
	io.KeySuper = (mods & GLFW_MOD_SUPER) != 0;
	#endif

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->keyCallback))
		glfwWindow->keyCallback(window, key, scancode, action, mods);
}
void glfw::WindowWrapper::s_charCallback(GLFWwindow* window, unsigned int codepoint) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	#if defined(IMGUI)
	ImGuiIO& io = ImGui::GetIO();
	io.AddInputCharacter(codepoint);
	#endif

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->charCallback))
		glfwWindow->charCallback(window, codepoint);
}
void glfw::WindowWrapper::s_charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->charModsCallback))
		glfwWindow->charModsCallback(window, codepoint, mods);
}
void glfw::WindowWrapper::s_dropCallback(GLFWwindow* window, int path_count, const char* paths[]) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->dropCallback))
		glfwWindow->dropCallback(window, path_count, paths);
}
void glfw::WindowWrapper::s_scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	#if defined(IMGUI)
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += (float)xoffset;
	io.MouseWheel += (float)yoffset;
	#endif

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->scrollCallback))
		glfwWindow->scrollCallback(window, xoffset, yoffset);
}
void glfw::WindowWrapper::s_cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->cursorPositionCallback))
		glfwWindow->cursorPositionCallback(window, xpos, ypos);
}
void glfw::WindowWrapper::s_windowPositionCallback(GLFWwindow* window, int xpos, int ypos) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->windowPositionCallback))
		glfwWindow->windowPositionCallback(window, xpos, ypos);
}
void glfw::WindowWrapper::s_windowSizeCallback(GLFWwindow* window, int width, int height) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->windowSizeCallback))
		glfwWindow->windowSizeCallback(window, width, height);
}
void glfw::WindowWrapper::s_cursorEnterCallback(GLFWwindow* window, int entered) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->cursorEnterCallback))
		glfwWindow->cursorEnterCallback(window, entered);
}
void glfw::WindowWrapper::s_windowCloseCallback(GLFWwindow* window) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->windowCloseCallback))
		glfwWindow->windowCloseCallback(window);
}
void glfw::WindowWrapper::s_mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);
	if (glfwWindow == nullptr)
		return;

	int mouseButtonIndex = glfwWindow->input.getMouseButtonIndex((MouseButtonCode)button);
	if (action == GLFW_PRESS) {
		glfwWindow->input.mouseButtons[mouseButtonIndex].justPressed = true;
		glfwWindow->input.mouseButtons[mouseButtonIndex].pressed = true;
	}
	if (action == GLFW_RELEASE) {
		glfwWindow->input.mouseButtons[mouseButtonIndex].justReleased = true;
		glfwWindow->input.mouseButtons[mouseButtonIndex].pressed = false;
	}

	glfwWindow->input.mouseButtonsToReset.push_front(&glfwWindow->input.mouseButtons[mouseButtonIndex]);

	#if defined(IMGUI)
	ImGuiIO& io = ImGui::GetIO();
	if (button >= 0 && button < IM_ARRAYSIZE(io.MouseDown))
		io.MouseDown[button] = (action == GLFW_PRESS);
	#endif

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->mouseButtonCallback))
		glfwWindow->mouseButtonCallback(window, button, action, mods);
}
void glfw::WindowWrapper::s_windowFocusCallback(GLFWwindow* window, int focused) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->windowFocusCallback))
		glfwWindow->windowFocusCallback(window, focused);
}
void glfw::WindowWrapper::s_windowIconifyCallback(GLFWwindow* window, int iconified) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->windowIconifyCallback))
		glfwWindow->windowIconifyCallback(window, iconified);
}
void glfw::WindowWrapper::s_windowRefreshCallback(GLFWwindow* window) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->windowRefreshCallback))
		glfwWindow->windowRefreshCallback(window);
}
void glfw::WindowWrapper::s_windowMaximizeCallback(GLFWwindow* window, int maximized) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->windowMaximizeCallback))
		glfwWindow->windowMaximizeCallback(window, maximized);
}
void glfw::WindowWrapper::s_frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->frameBufferSizeCallback))
		glfwWindow->frameBufferSizeCallback(window, width, height);
}
void glfw::WindowWrapper::s_windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale) {
	WindowWrapper* glfwWindow = (WindowWrapper*)glfwGetWindowUserPointer(window);

	// Forward callback if anything is subscribed
	if (static_cast<bool>(glfwWindow->windowContentScaleCallback))
		glfwWindow->windowContentScaleCallback(window, xscale, yscale);
}

// Object | public

// Constructor / Destructor
glfw::WindowWrapper::WindowWrapper() : glfw::WindowWrapper(defaultWidth, defaultHeight, s_defaultName, nullptr) {
	// All code is ran through the other contructor
	// Do not place code here. It might not be ran
}
glfw::WindowWrapper::WindowWrapper(int width, int height, const std::string& title, GLFWmonitor* monitor) {
	if (!glfwInit())
		return;
	
	// Set window hints prior to creation (remove this in production. This needs to be set outside of this class)	
	#if defined(VULKAN_ENGINE)
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	#endif

	#if defined(OPENGL_ENGINE)
	glfwWindowHint(GLFW_MAXIMIZED, true);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	#endif

	GLFWwindow* share = nullptr;
	if (windowList.size() > 0) {
		WindowWrapper* windowWrapper = windowList.front();
		window = windowWrapper->window;
	}

	// Create and set window user pointer
	window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
	glfwSetWindowUserPointer(window, this);

	#if defined(OPENGL_ENGINE)
		glfwMakeContextCurrent(window);
		assert(glewInit() == GLEW_OK);
	#endif

	// Set callbacks
	glfwSetKeyCallback(window, s_keyCallback);
	glfwSetCharCallback(window, s_charCallback);
	glfwSetCharModsCallback(window, s_charModsCallback);
	glfwSetDropCallback(window, s_dropCallback);
	glfwSetScrollCallback(window, s_scrollCallback);
	glfwSetCursorPosCallback(window, s_cursorPositionCallback);
	glfwSetWindowPosCallback(window, s_windowPositionCallback);
	glfwSetWindowSizeCallback(window, s_windowSizeCallback);
	glfwSetCursorEnterCallback(window, s_cursorEnterCallback);
	glfwSetWindowCloseCallback(window, s_windowCloseCallback);
	glfwSetMouseButtonCallback(window, s_mouseButtonCallback);
	glfwSetWindowFocusCallback(window, s_windowFocusCallback);
	glfwSetWindowIconifyCallback(window, s_windowIconifyCallback);
	glfwSetWindowRefreshCallback(window, s_windowRefreshCallback);
	glfwSetWindowMaximizeCallback(window, s_windowMaximizeCallback);
	glfwSetFramebufferSizeCallback(window, s_frameBufferSizeCallback);

	windowList.push_back(this);
	node = std::prev(windowList.end());
}
glfw::WindowWrapper::~WindowWrapper() {
	glfwDestroyWindow(window);
	windowList.erase(node);
}

// Getters
GLFWwindow* glfw::WindowWrapper::getWindow() const {
	return window;
}
