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
 * File: Window.h
 * Author: Christopher Barrios Agosto
 * Created on: 29DEC2024
 *
 * Description:
 *  Wrapper class around GLFW window pointer.
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <string>
#include <list>
#include <functional>

#if defined(OPENGL_ENGINE)
// Dependencies | glew
#include <glew/glew.h>
#endif

// Dependencies | glfw
#include <glfw/glfw3.h>

#if defined(IMGUI)
// Dependencies | imgui
#include <imgui/imgui.h>
#endif

// Dependencies | glfw_engine
#include "Input.h"

namespace glfw {
	class WindowWrapper {
		// Static
		private:
			// Properties
			static std::list<WindowWrapper*> windowList;

		public:
			// Properties
			static int defaultWidth;
			static int defaultHeight;
			static std::string s_defaultName;

			// Getters
			static std::list<WindowWrapper*> getWindowList();

			// Callbacks
			static void s_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void s_charCallback(GLFWwindow* window, unsigned int codepoint);
			static void s_charModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
			static void s_dropCallback(GLFWwindow* window, int path_count, const char* paths[]);
			static void s_scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
			static void s_cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
			static void s_windowPositionCallback(GLFWwindow* window, int xpos, int ypos);
			static void s_windowSizeCallback(GLFWwindow* window, int width, int height);
			static void s_cursorEnterCallback(GLFWwindow* window, int entered);
			static void s_windowCloseCallback(GLFWwindow* window);
			static void s_mouseButtonCallback(GLFWwindow* window, int button, int actuion, int mods);
			static void s_windowFocusCallback(GLFWwindow* window, int focused);
			static void s_windowIconifyCallback(GLFWwindow* window, int iconified);
			static void s_windowRefreshCallback(GLFWwindow* window);
			static void s_windowMaximizeCallback(GLFWwindow* window, int maximized);
			static void s_frameBufferSizeCallback(GLFWwindow* window, int width, int height);
			static void s_windowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);

		// Object
		private:
			// Properties
			GLFWwindow* window = nullptr;
			std::list<glfw::WindowWrapper*>::iterator node;

		public:
			// Properties
			glfw::Input input;

			std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)> keyCallback;
			std::function<void(GLFWwindow* window, unsigned int codepoint)> charCallback;
			std::function<void(GLFWwindow* window, unsigned int codepoint, int mods)> charModsCallback;
			std::function<void(GLFWwindow* window, int path_count, const char* paths[])> dropCallback;
			std::function<void(GLFWwindow* window, double xoffset, double yoffset)> scrollCallback;
			std::function<void(GLFWwindow* window, double xpos, double ypos)> cursorPositionCallback;
			std::function<void(GLFWwindow* window, int xpos, int ypos)> windowPositionCallback;
			std::function<void(GLFWwindow* window, int width, int height)> windowSizeCallback;
			std::function<void(GLFWwindow* window, int entered)> cursorEnterCallback;
			std::function<void(GLFWwindow* window)> windowCloseCallback;
			std::function<void(GLFWwindow* window, int button, int actuion, int mods)> mouseButtonCallback;
			std::function<void(GLFWwindow* window, int focused)> windowFocusCallback;
			std::function<void(GLFWwindow* window, int iconified)> windowIconifyCallback;
			std::function<void(GLFWwindow* window)> windowRefreshCallback;
			std::function<void(GLFWwindow* window, int maximized)> windowMaximizeCallback;
			std::function<void(GLFWwindow* window, int width, int height)> frameBufferSizeCallback;
			std::function<void(GLFWwindow* window, float xscale, float yscale)> windowContentScaleCallback;

			// Constructor / Destructor
			WindowWrapper();
			WindowWrapper(int width, int height, const std::string& title, GLFWmonitor* monitor);
			~WindowWrapper();

			// Getters
			GLFWwindow* getWindow() const;
	};
}
