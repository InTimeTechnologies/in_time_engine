#pragma once

// Dependencies | in_time_engine | window | backend
#include <in_time_engine/window/backend/IWindowBackend.h>

namespace it {
	class SimulatedWindowBackend : public IWindowBackend {
		// Object
		public:
			// Constructor / Destructor
			SimulatedWindowBackend() = delete;
			SimulatedWindowBackend(Window& owner);
			SimulatedWindowBackend(const SimulatedWindowBackend& other) = delete;
			SimulatedWindowBackend(SimulatedWindowBackend&& other) noexcept = delete;
			~SimulatedWindowBackend() = default;

			// Operators | assignment
			SimulatedWindowBackend& operator=(const SimulatedWindowBackend& other) = delete;
			SimulatedWindowBackend& operator=(SimulatedWindowBackend&& other) noexcept = delete;

			// IWindowBackend | Getters
			void* getHandle() override;

			std::string getTitle() const override;
			int getX() const override;
			int getY() const override;
			int getWidth() const override;
			int getHeight() const override;

			// IWindowBackend | Setters
			void setTitle(const std::string& title) override;
			void setPosition(int x, int y) override;
			void setSize(int width, int height) override;

			// IWindowBackend | Functions
			void* init() override;
			void show() override;
			void hide() override;
	};
}
