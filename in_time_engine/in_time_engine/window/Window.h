#pragma once

// Dependencies | std
#include <string>

namespace it {
	struct BackendObjectHandle {
		// Getters
		virtual void* getHandle() = 0;
	};

	class Window {
		// Static
		public:
			// Properties
			static int s_defaultWidth;
			static int s_defaultHeight;
			static std::string s_defaultTitle;

		// Object
		private:
			// Properties
			BackendObjectHandle* backendObjectHandle{ nullptr };

			// Properties
			std::string title;
			int x, y;
			int width, height;

		public:
			// Constructor / Destructor
			Window();
			Window(int width, int height, const std::string& title);
			Window(const Window& other) = delete;
			Window(Window&& other) = delete;
			~Window();

			// Operators | assignment
			Window& operator=(const Window& other) = delete;
			Window& operator=(Window&& other) = delete;

			// Operators | equality
			bool operator==(const Window& other) const;

			// Getters
			std::string getTitle() const;
			int getWidth() const;
			int getHeight() const;
			int getX() const;
			int getY() const;

			// Setters
			void setTitle(const std::string& title);
			void setSize(int width, int height);
			void setPosition(int x, int y);

			// Feeders
			void feedTitle(const std::string& title);
			void feedSize(int width, int height);
			void feedPosition(int x, int y);
	};
}
