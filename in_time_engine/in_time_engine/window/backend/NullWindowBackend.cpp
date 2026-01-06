#include "NullWindowBackend.h"

namespace it {
	// class NullWindowBackend

	// Object | public

	// Getters
	void* NullWindowBackend::getHandle() {
		return nullptr;
	}

	std::string NullWindowBackend::getTitle() const {
		return std::string();
	}
	int NullWindowBackend::getX() const {
		return 0;
	}
	int NullWindowBackend::getY() const {
		return 0;
	}
	int NullWindowBackend::getWidth() const {
		return 0;
	}
	int NullWindowBackend::getHeight() const {
		return 0;
	}

	// Setters
	void NullWindowBackend::setTitle(const std::string& title) {
		// Left empty intentionally
	}
	void NullWindowBackend::setPosition(int x, int y) {
		// Left empty intentionally
	}
	void NullWindowBackend::setSize(int width, int height) {
		// Left empty intentionally
	}
}
