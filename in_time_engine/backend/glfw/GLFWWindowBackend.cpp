#include "GLFWWindowBackend.h"

// Dependencies | std
#include <cassert>

// Dependencies | in_time_engine | window
#include <in_time_engine/window/Window.h>

// Dependencies | backend | glfw
#include "GLFWPlatformBackend.h"

namespace it {
	// class GLFWWindowBackend

	// Oject | public

	// Constructor / Destructor
	GLFWWindowBackend::GLFWWindowBackend(Window& owner) : IWindowBackend(owner) {
		
	}
	GLFWWindowBackend::~GLFWWindowBackend() {
		if (glfwWindow != nullptr) {
			glfwDestroyWindow(glfwWindow);
			glfwWindow = nullptr;
		}
	}

	// IWIndowBackend | Getters
	void* GLFWWindowBackend::getHandle() {
		return glfwWindow;
	}

	std::string GLFWWindowBackend::getTitle() const {
		return glfwGetWindowTitle(glfwWindow);
	}
	int GLFWWindowBackend::getX() const {
		int x, y;
		glfwGetWindowPos(glfwWindow, &x, &y);
		return x;
	}
	int GLFWWindowBackend::getY() const {
		int x, y;
		glfwGetWindowPos(glfwWindow, &x, &y);
		return y;
	}
	int GLFWWindowBackend::getWidth() const {
		int width, height;
		glfwGetWindowPos(glfwWindow, &width, &height);
		return width;
	}
	int GLFWWindowBackend::getHeight() const {
		int width, height;
		glfwGetWindowPos(glfwWindow, &width, &height);
		return width;
	}

	// IWIndowBackend | Setters
	void GLFWWindowBackend::setTitle(const std::string& title) {
		glfwSetWindowTitle(glfwWindow, title.c_str());
	}
	void GLFWWindowBackend::setPosition(int x, int y) {
		glfwSetWindowPos(glfwWindow, x, y);
	}
	void GLFWWindowBackend::setSize(int width, int height) {
		glfwSetWindowSize(glfwWindow, width, height);
	}

	// IWIndowBackend | Functions
	void* GLFWWindowBackend::init() {
		assert(glfwWindow == nullptr && "glfwWindow != nullptr, glfwWindow was previously created.");
		glfwWindow = glfwCreateWindow(owner.getWidth(), owner.getHeight(), owner.getTitle().c_str(), nullptr, nullptr);
		assert(glfwWindow != nullptr && "glfwWindow == nullptr, failed to create glfw window.");
		if (glfwWindow == nullptr)
			return nullptr;

		glfwSetWindowPos(glfwWindow, owner.getX(), owner.getY());

		// Set callbacks
		GLFWPlatformBackend* platformBackend = GLFWPlatformBackend::s_getSingleton();

		if (platformBackend->mouseKeyboardInput != nullptr)
			glfwSetKeyCallback(glfwWindow, GLFWPlatformBackend::s_keyCallback);

		return glfwWindow;
	}
	void GLFWWindowBackend::show() {
		if (glfwWindow == nullptr)
			init();
		glfwShowWindow(glfwWindow);
	}
	void GLFWWindowBackend::hide() {
		glfwHideWindow(glfwWindow);
	}
}
