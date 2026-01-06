#pragma once

// Dependencies | in_time_engine | window | backend
#include "IWindowBackend.h"

namespace it {
	class SimulatedWindowBackend : public IWindowBackend {
		// Object
		public:
			// Properties
			void* handle{ nullptr };
			std::string title{ "Simulated Window Backend" };
			int x{ 0 }, y{ 0 };
			int width{ 800 }, height{ 600 };

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
	};
}
