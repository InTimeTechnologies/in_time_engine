#include <in_time_engine/window/Window.h>

// Dependencies | std
#include <cassert>

// Dependencies | glfw
#include <GLFW/glfw3.h>

// Dependencies | backend | glfw
#include "GLFWBackend.h"

namespace it {
	// Functions
	static GLFWwindow* toGLFWWindow(void* pointer) {
		assert(pointer != nullptr && "implementation pointer is nullptr.");
		GLFWwindow* glfwWindow = reinterpret_cast<GLFWwindow*>(pointer);
		return glfwWindow;
	}

	// class Window

	// Static | public

	// Properties
	int Window::s_defaultWidth = 800;
	int Window::s_defaultHeight = 600;
	std::string Window::s_defaultTitle = "GLFW Window";

	// Object | public

	// Constructor / Destructor
	Window::Window() {
		GLFWwindow* glfwWindow = glfwCreateWindow(s_defaultWidth, s_defaultHeight, s_defaultTitle.c_str(), nullptr, nullptr);
		assert(glfwWindow != nullptr && "failed to create glfw window.");
		glfwSetWindowUserPointer(glfwWindow, this);
		glfwSetKeyCallback(glfwWindow, GLFWBackend::s_keyCallback);
		backendObjectHandle = glfwWindow;

		glfwMakeContextCurrent(glfwWindow);
	}
	Window::Window(int width, int height, const std::string& title) {
		GLFWwindow* glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		assert(glfwWindow != nullptr && "failed to create glfw window.");
		glfwSetWindowUserPointer(glfwWindow, this);
		glfwSetKeyCallback(glfwWindow, GLFWBackend::s_keyCallback);
		backendObjectHandle = glfwWindow;

		glfwMakeContextCurrent(glfwWindow);
	}
	Window::~Window() {
		if (backendObjectHandle == nullptr)
			return;
		GLFWwindow* glfwWindow = reinterpret_cast<GLFWwindow*>(backendObjectHandle);
		glfwDestroyWindow(glfwWindow);
		glfwWindow = nullptr;
	}

	// Operators | equality
	bool Window::operator==(const Window& other) const {
		return backendObjectHandle == other.backendObjectHandle;
	}
	
	// Getters
	std::string Window::getTitle() const {
		GLFWwindow* glfwWindow = toGLFWWindow(backendObjectHandle);
		std::string title = glfwGetWindowTitle(glfwWindow);
		return title;
	}
	int Window::getWidth() const {
		GLFWwindow* glfwWindow = toGLFWWindow(backendObjectHandle);
		int width, height;
		glfwGetWindowSize(glfwWindow, &width, &height);
		return width;
	}
	int Window::getHeight() const {
		GLFWwindow* glfwWindow = toGLFWWindow(backendObjectHandle);
		int width, height;
		glfwGetWindowSize(glfwWindow, &width, &height);
		return height;
	}
	int Window::getX() const {
		GLFWwindow* glfwWindow = toGLFWWindow(backendObjectHandle);
		int x, y;
		glfwGetWindowPos(glfwWindow, &x, &y);
		return x;
	}
	int Window::getY() const {
		GLFWwindow* glfwWindow = toGLFWWindow(backendObjectHandle);
		int x, y;
		glfwGetWindowPos(glfwWindow, &x, &y);
		return y;
	}

	// Setters
	void Window::setTitle(const std::string& title) {
		GLFWwindow* glfwWindow = toGLFWWindow(backendObjectHandle);
		glfwSetWindowTitle(glfwWindow, title.c_str());
	}
	void Window::setSize(int width, int height) {
		GLFWwindow* glfwWindow = toGLFWWindow(backendObjectHandle);
		glfwSetWindowSize(glfwWindow, width, height);
	}
	void Window::setPosition(int width, int height) {
		GLFWwindow* glfwWindow = toGLFWWindow(backendObjectHandle);
		glfwSetWindowPos(glfwWindow, width, height);
	}
}
