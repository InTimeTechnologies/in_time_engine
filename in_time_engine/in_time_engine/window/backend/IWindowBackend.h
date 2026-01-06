#pragma once

// Dependencies | std
#include <string>

namespace it {
	// Forward declarations
	class Window;

	class IWindowBackend {
		// Object
		public:
			// Properties
			Window& owner;

			// Constructor / Destructor
			IWindowBackend() = delete;
			IWindowBackend(Window& owner) : owner(owner) {}
			IWindowBackend(const IWindowBackend& other) = delete;
			IWindowBackend(IWindowBackend&& other) noexcept = delete;
			~IWindowBackend() = default;

			// Operator | assignment
			IWindowBackend& operator=(const IWindowBackend& other) = delete;
			IWindowBackend& operator=(IWindowBackend&& other) noexcept = delete;

			// Getters
			virtual void* getHandle() = 0;

			virtual std::string getTitle() const = 0;
			virtual int getX() const = 0;
			virtual int getY() const = 0;
			virtual int getWidth() const = 0;
			virtual int getHeight() const = 0;

			// Setters
			virtual void setTitle(const std::string& title) = 0;
			virtual void setPosition(int x, int y) = 0;
			virtual void setSize(int width, int height) = 0;

			// Functions
			virtual void* init() = 0;
			virtual void show() = 0;
			virtual void hide() = 0;
	};
}
