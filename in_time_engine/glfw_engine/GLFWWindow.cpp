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

#include "GLFWWindow.h"

// Dependencies | std
#include <cassert>

namespace glfw {
	// class Window

	// Static | public

	// Properties
	int Window::s_defaultWidth = 800;
	int Window::s_defaultHeight = 600;
	std::string Window::s_defaultTitle = "GLFW Window";
#if defined(OPENGL)
	std::vector<std::pair<int, int>> Window::s_defaultWindowHints{
		{ GLFW_CONTEXT_VERSION_MAJOR, 4 },
		{ GLFW_CONTEXT_VERSION_MINOR, 6 },
		{ GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE },
		{ GLFW_SAMPLES, 4 }
	};
#elif defined (VULKAN)
	std::vector<std::pair<int, int>> Window::s_defaultWindowHints{
		{ GLFW_SLIENT_API, GLFW_NO_API }
	};
#else
	std::vector<std::pair<int, int>> Window::s_defaultWindowHints{};
#endif

	// Callbacks
	void Window::s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);
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

		if (glfwWindow->imGuiContext != nullptr) {
			ImGui::SetCurrentContext(glfwWindow->imGuiContext);
			ImGuiIO& io = ImGui::GetIO();
			if (action == GLFW_PRESS)
				io.KeysData[key].Down = true;
			else if (action == GLFW_RELEASE)
				io.KeysData[key].Down = false;

			io.KeyCtrl = (mods & GLFW_MOD_CONTROL) != 0;
			io.KeyShift = (mods & GLFW_MOD_SHIFT) != 0;
			io.KeyAlt = (mods & GLFW_MOD_ALT) != 0;
			io.KeySuper = (mods & GLFW_MOD_SUPER) != 0;
		}

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->keyCallback))
			glfwWindow->keyCallback(window, key, scancode, action, mods);
	}
	void Window::s_charCallback(GLFWwindow* window, unsigned int codepoint) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		if (glfwWindow->imGuiContext != nullptr) {
			ImGui::SetCurrentContext(glfwWindow->imGuiContext);
			ImGuiIO& io = ImGui::GetIO();
			io.AddInputCharacter(codepoint);
		}

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->charCallback))
			glfwWindow->charCallback(window, codepoint);
	}
	void Window::s_charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->charModsCallback))
			glfwWindow->charModsCallback(window, codepoint, mods);
	}
	void Window::s_dropCallback(GLFWwindow* window, int path_count, const char* paths[]) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->dropCallback))
			glfwWindow->dropCallback(window, path_count, paths);
	}
	void Window::s_scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		if (glfwWindow->imGuiContext != nullptr) {
			ImGui::SetCurrentContext(glfwWindow->imGuiContext);
			ImGuiIO& io = ImGui::GetIO();
			io.MouseWheelH += static_cast<float>(xoffset);
			io.MouseWheel += static_cast<float>(yoffset);
		}

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->scrollCallback))
			glfwWindow->scrollCallback(window, xoffset, yoffset);
	}
	void Window::s_cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->cursorPositionCallback))
			glfwWindow->cursorPositionCallback(window, xpos, ypos);
	}
	void Window::s_windowPositionCallback(GLFWwindow* window, int xpos, int ypos) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->windowPositionCallback))
			glfwWindow->windowPositionCallback(window, xpos, ypos);
	}
	void Window::s_windowSizeCallback(GLFWwindow* window, int width, int height) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->windowSizeCallback))
			glfwWindow->windowSizeCallback(window, width, height);
	}
	void Window::s_cursorEnterCallback(GLFWwindow* window, int entered) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->cursorEnterCallback))
			glfwWindow->cursorEnterCallback(window, entered);
	}
	void Window::s_windowCloseCallback(GLFWwindow* window) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->windowCloseCallback))
			glfwWindow->windowCloseCallback(window);
	}
	void Window::s_mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);
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

		ImGuiIO& io = ImGui::GetIO();
		if (button >= 0 && button < IM_ARRAYSIZE(io.MouseDown))
			io.MouseDown[button] = (action == GLFW_PRESS);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->mouseButtonCallback))
			glfwWindow->mouseButtonCallback(window, button, action, mods);
	}
	void Window::s_windowFocusCallback(GLFWwindow* window, int focused) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->windowFocusCallback))
			glfwWindow->windowFocusCallback(window, focused);
	}
	void Window::s_windowIconifyCallback(GLFWwindow* window, int iconified) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->windowIconifyCallback))
			glfwWindow->windowIconifyCallback(window, iconified);
	}
	void Window::s_windowRefreshCallback(GLFWwindow* window) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->windowRefreshCallback))
			glfwWindow->windowRefreshCallback(window);
	}
	void Window::s_windowMaximizeCallback(GLFWwindow* window, int maximized) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->windowMaximizeCallback))
			glfwWindow->windowMaximizeCallback(window, maximized);
	}
	void Window::s_frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->frameBufferSizeCallback))
			glfwWindow->frameBufferSizeCallback(window, width, height);
	}
	void Window::s_windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale) {
		Window* glfwWindow = (Window*)glfwGetWindowUserPointer(window);

		// Forward callback if anything is subscribed
		if (static_cast<bool>(glfwWindow->windowContentScaleCallback))
			glfwWindow->windowContentScaleCallback(window, xscale, yscale);
	}

	// Object | public

	// Constructor / Destructor
	Window::Window() : Window(s_defaultWidth, s_defaultHeight, s_defaultTitle, nullptr, nullptr) {
		// All code is ran through the other contructor
		// Do not place code here. It might not be ran
	}
	Window::Window(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) {
		if (!glfwInit())
			return;

		// Set window hints prior to creation (remove this in production. This needs to be set outside of this class)	
		// glfwWindowHint(GLFW_MAXIMIZED, true);
		// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		// glfwWindowHint(GLFW_SAMPLES, 4);
		for (size_t i = 0; i < s_defaultWindowHints.size(); i++) {
			int hint = s_defaultWindowHints[i].first;
			int value = s_defaultWindowHints[i].second;
			glfwWindowHint(hint, value);
		}

		// Create window
		window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
		glfwSetWindowUserPointer(window, this);

		glfwMakeContextCurrent(window);
		bool glewInitiated = glewInit();
		assert(glewInitiated == GLEW_OK);

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
	}
	Window::Window(const Window& other) {
		int width{ 0 }, height{ 0 };
		glfwGetWindowSize(other.window, &width, &height);

		// Copy properties
		window = other.window;
		window = glfwCreateWindow(width, height, s_defaultTitle.c_str(), nullptr, other.window);
		input = other.input;

		// Copy callbacks
		keyCallback = other.keyCallback;
		charCallback = other.charCallback;
		charModsCallback = other.charModsCallback;
		dropCallback = other.dropCallback;
		scrollCallback = other.scrollCallback;
		cursorPositionCallback = other.cursorPositionCallback;
		windowPositionCallback = other.windowPositionCallback;
		windowSizeCallback = other.windowSizeCallback;
		cursorEnterCallback = other.cursorEnterCallback;
		windowCloseCallback = other.windowCloseCallback;
		mouseButtonCallback = other.mouseButtonCallback;
		windowFocusCallback = other.windowFocusCallback;
		windowIconifyCallback = other.windowIconifyCallback;
		windowRefreshCallback = other.windowRefreshCallback;
		windowMaximizeCallback = other.windowMaximizeCallback;
		frameBufferSizeCallback = other.frameBufferSizeCallback;
	}
	Window::Window(Window&& other) noexcept {
		// Move properties
		window = other.window;
		other.window = nullptr;
		input = std::move(other.input);

		// Move callbacks
		keyCallback = std::move(other.keyCallback);
		charCallback = std::move(other.charCallback);
		charModsCallback = std::move(other.charModsCallback);
		dropCallback = std::move(other.dropCallback);
		scrollCallback = std::move(other.scrollCallback);
		cursorPositionCallback = std::move(other.cursorPositionCallback);
		windowPositionCallback = std::move(other.windowPositionCallback);
		windowSizeCallback = std::move(other.windowSizeCallback);
		cursorEnterCallback = std::move(other.cursorEnterCallback);
		windowCloseCallback = std::move(other.windowCloseCallback);
		mouseButtonCallback = std::move(other.mouseButtonCallback);
		windowFocusCallback = std::move(other.windowFocusCallback);
		windowIconifyCallback = std::move(other.windowIconifyCallback);
		windowRefreshCallback = std::move(other.windowRefreshCallback);
		windowMaximizeCallback = std::move(other.windowMaximizeCallback);
		frameBufferSizeCallback = std::move(other.frameBufferSizeCallback);
	}
	Window::~Window() {
		glfwDestroyWindow(window);
	}

	// Operators | asignment
	Window& Window::operator=(const Window& other) {
		int width{ 0 }, height{ 0 };
		glfwGetWindowSize(other.window, &width, &height);

		// Copy properties
		window = other.window;
		window = glfwCreateWindow(width, height, s_defaultTitle.c_str(), nullptr, other.window);
		input = other.input;

		// Copy callbacks
		keyCallback = other.keyCallback;
		charCallback = other.charCallback;
		charModsCallback = other.charModsCallback;
		dropCallback = other.dropCallback;
		scrollCallback = other.scrollCallback;
		cursorPositionCallback = other.cursorPositionCallback;
		windowPositionCallback = other.windowPositionCallback;
		windowSizeCallback = other.windowSizeCallback;
		cursorEnterCallback = other.cursorEnterCallback;
		windowCloseCallback = other.windowCloseCallback;
		mouseButtonCallback = other.mouseButtonCallback;
		windowFocusCallback = other.windowFocusCallback;
		windowIconifyCallback = other.windowIconifyCallback;
		windowRefreshCallback = other.windowRefreshCallback;
		windowMaximizeCallback = other.windowMaximizeCallback;
		frameBufferSizeCallback = other.frameBufferSizeCallback;

		return *this;
	}
	Window& Window::operator=(Window&& other) noexcept {
		int width{ 0 }, height{ 0 };
		glfwGetWindowSize(other.window, &width, &height);

		// Move properties
		window = other.window;
		other.window = nullptr;
		input = std::move(other.input);

		// Move callbacks
		keyCallback = std::move(other.keyCallback);
		charCallback = std::move(other.charCallback);
		charModsCallback = std::move(other.charModsCallback);
		dropCallback = std::move(other.dropCallback);
		scrollCallback = std::move(other.scrollCallback);
		cursorPositionCallback = std::move(other.cursorPositionCallback);
		windowPositionCallback = std::move(other.windowPositionCallback);
		windowSizeCallback = std::move(other.windowSizeCallback);
		cursorEnterCallback = std::move(other.cursorEnterCallback);
		windowCloseCallback = std::move(other.windowCloseCallback);
		mouseButtonCallback = std::move(other.mouseButtonCallback);
		windowFocusCallback = std::move(other.windowFocusCallback);
		windowIconifyCallback = std::move(other.windowIconifyCallback);
		windowRefreshCallback = std::move(other.windowRefreshCallback);
		windowMaximizeCallback = std::move(other.windowMaximizeCallback);
		frameBufferSizeCallback = std::move(other.frameBufferSizeCallback);

		return *this;
	}

	// Operators | comparison
	bool Window::operator==(const Window& other) const {
		return window == other.window;
	}

	// Getters
	GLFWwindow* Window::getWindow() const {
		return window;
	}

	// Functions
	bool Window::hasImGuiContext() const {
		return imGuiContext != nullptr;
	}
	ImGuiContext* Window::createImGuiContext() {
		imGuiContext = ImGui::CreateContext();
		return imGuiContext;
	}
	void Window::destroyImGuiContext() {
		ImGui::DestroyContext(imGuiContext);
		imGuiContext = nullptr;
	}
	void Window::makeImGuiContextCurrent() {
		ImGui::SetCurrentContext(imGuiContext);
	}
}
