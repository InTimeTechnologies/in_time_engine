#pragma once

// Dependencies | std
#include <string>

// Dependencies | in_time_engine | Window
#include "backend/IWindowBackend.h"
#include "backend/IWindowPlatformBackend.h"

namespace it {
	class Window {
		// Friends
		friend class WindowManager;

		// Static
		public:
			// Properties
			static std::string s_defaultTitle;
			static int s_defaultX, s_defaultY;
			static int s_defaultWidth, s_defaultHeight;

		// Object
		private:
			// Properties
			IWindowBackend* iWindowBackend{ nullptr };

			// Properties
			std::string title{ s_defaultTitle };
			int x{ s_defaultX }, y{ s_defaultY };
			int width{ s_defaultWidth }, height{ s_defaultHeight };
			bool visible{ false };

		public:
			// Constructor / Destructor
			Window();
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
			int getX() const;
			int getY() const;
			int getWidth() const;
			int getHeight() const;

			// Setters
			void setTitle(const std::string& title);
			void setPosition(int x, int y);
			void setSize(int width, int height);

			// Functions
			void show();
			void hide();
	};
}
