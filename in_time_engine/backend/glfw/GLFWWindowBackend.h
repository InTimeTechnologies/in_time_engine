#pragma once

// Dependencies | in_time_engine | window | backend
#include <in_time_engine/window/backend/IWindowBackend.h>

// Dependencies | glfw
#include <GLFW/glfw3.h>

namespace it {
	class GLFWWindowBackend : public IWindowBackend {
		// Friends
		friend class EngineConfigurator;

		// Object
		public:
			// Properties
			GLFWwindow* glfwWindow{ nullptr };

			// Constructor / Destructor
			GLFWWindowBackend() = delete;
			GLFWWindowBackend(Window& owner);
			GLFWWindowBackend(const GLFWWindowBackend& other) = delete;
			GLFWWindowBackend(GLFWWindowBackend&& other) noexcept = delete;
			~GLFWWindowBackend();

			// Operators | assignment
			GLFWWindowBackend& operator=(const GLFWWindowBackend& other) = delete;
			GLFWWindowBackend& operator=(GLFWWindowBackend&& other) noexcept = delete;

			// Getters
			void* getHandle() override;

			std::string getTitle() const override;
			int getX() const override;
			int getY() const override;
			int getWidth() const override;
			int getHeight() const override;

			// Setters
			void setTitle(const std::string& title) override;
			void setPosition(int x, int y) override;
			void setSize(int width, int height) override;

			// Functions
			void* init() override;
			void show() override;
			void hide() override;
	};
}
