#include "SimulatedWindowBackend.h"

namespace it {
	// class SimulatedWindowBackend

	// Object | public

	// Getters
	void* SimulatedWindowBackend::getHandle() {
		return handle;
	}

	std::string SimulatedWindowBackend::getTitle() const {
		return title;
	}
	int SimulatedWindowBackend::getX() const {
		return x;
	}
	int SimulatedWindowBackend::getY() const {
		return y;
	}
	int SimulatedWindowBackend::getWidth() const {
		return width;
	}
	int SimulatedWindowBackend::getHeight() const {
		return height;
	}

	// Setters
	void SimulatedWindowBackend::setTitle(const std::string& title) {
		this->title = title;
	}
	void SimulatedWindowBackend::setPosition(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void SimulatedWindowBackend::setSize(int width, int height) {
		this->width = width;
		this->height = height;
	}
}