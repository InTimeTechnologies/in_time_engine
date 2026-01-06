#include "Window.h"

// Dependencies | std
#include <cassert>

namespace it {
	// class Window

	// Static | public

	// Properties
	std::string Window::s_defaultTitle{};
	int Window::s_defaultX{ 200 };
	int Window::s_defaultY{ 200 };
	int Window::s_defaultWidth{ 800 };
	int Window::s_defaultHeight{ 600 };

	// Object | public

	// Constructor / Destructor
	Window::Window() {

	}
	Window::~Window() {
		if (iWindowBackend != nullptr) {
			delete iWindowBackend;
			iWindowBackend = nullptr;
		}
	}

	// Operators | equality
	bool Window::operator==(const Window& other) const {
		assert(iWindowBackend != nullptr && "iWindowBackend == nullptr");
		return iWindowBackend == other.iWindowBackend;
	}

	// Getters
	std::string Window::getTitle() const {
		return title;
	}
	int Window::getX() const {
		return x;
	}
	int Window::getY() const {
		return y;
	}
	int Window::getWidth() const {
		return width;
	}
	int Window::getHeight() const {
		return height;
	}
	
	// Setters
	void Window::setTitle(const std::string& title) {
		if (iWindowBackend != nullptr)
			iWindowBackend->setTitle(title);
		this->title = title;
	}
	void Window::setPosition(int x, int y) {
		if (iWindowBackend != nullptr)
			iWindowBackend->setPosition(x, y);
		this->x = x;
		this->y = y;
	}
	void Window::setSize(int width, int height) {
		if (iWindowBackend != nullptr)
			iWindowBackend->setSize(width, height);
		this->width = width;
		this->height = height;
	}

	// Funtions
	void Window::show() {
		visible = true;

		if (iWindowBackend == nullptr)
			return;

		if (iWindowBackend->getHandle() == nullptr)
			iWindowBackend->init();

		iWindowBackend->show();
	}
	void Window::hide() {
		if (iWindowBackend == nullptr)
			return;

		if (iWindowBackend != nullptr)
			iWindowBackend->hide();
	}
}
