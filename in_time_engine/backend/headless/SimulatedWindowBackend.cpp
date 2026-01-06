#include "SimulatedWindowBackend.h"

// Dependencies | in_time_engine | window
#include <in_time_engine/window/Window.h>

namespace it {
	// class SimulatedWindowBackend

	// Object | public

	// Constructor / Destructor
	SimulatedWindowBackend::SimulatedWindowBackend(Window& onwer) : IWindowBackend(owner) {
		// Intentionally left empty
	}

	// IWindowBackend | Getters
	void* SimulatedWindowBackend::getHandle() {
		return nullptr;
	}

	std::string SimulatedWindowBackend::getTitle() const {
		return owner.getTitle();
	}
	int SimulatedWindowBackend::getX() const {
		return owner.getX();
	}
	int SimulatedWindowBackend::getY() const {
		return owner.getY();
	}
	int SimulatedWindowBackend::getWidth() const {
		return owner.getWidth();
	}
	int SimulatedWindowBackend::getHeight() const {
		return owner.getHeight();
	}

	// Setters
	void SimulatedWindowBackend::setTitle(const std::string& title) {
		// Intentionally left empty
	}
	void SimulatedWindowBackend::setPosition(int x, int y) {
		// Intentionally left empty
	}
	void SimulatedWindowBackend::setSize(int width, int height) {
		// Intentionally left empty
	}

	// Functions
	void* SimulatedWindowBackend::init() {
		return nullptr;
	}
	void SimulatedWindowBackend::show() {
		// Intentionally left empty
	}
	void SimulatedWindowBackend::hide() {
		// Intentionally left empty
	}
}