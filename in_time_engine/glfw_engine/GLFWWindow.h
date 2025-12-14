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

// Dependencies | glew
#include <GL/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

// Dependencies | glfw_engine
#include "GLFWInput.h"

// Dependencies | imgui
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

namespace glfw {
	class Window {
		// Static
		public:
			// Properties
			static int s_defaultWidth;
			static int s_defaultHeight;
			static std::string s_defaultTitle;

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
			std::list<glfw::Window*>::iterator node;
			std::string title;

		public:
			// Properties
			ImGuiContext* imGuiContext{ nullptr };

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
			Window();
			Window(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* glfwWindow);
			Window(const Window& other);
			Window(Window&& other) noexcept;
			~Window();

			// Operators | asignment
			Window& operator=(const Window& other);
			Window& operator=(Window&& other) noexcept;

			// Operators | comparison
			bool operator==(const Window& other) const;

			// Getters
			GLFWwindow* getWindow() const;

			// Functions
			ImGuiContext* createImGuiContext();
			void destroyImGuiContext();
			bool hasImGuiContext() const;
			void makeImGuiContextCurrent();
	};
}
