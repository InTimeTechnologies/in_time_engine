#pragma once

// Dependencies | std
#include <string>

// Dependencies | in_time_engine | window | backend
#include "IWindowBackend.h"

namespace it {
	class NullWindowBackend : public IWindowBackend {
		// Object
		public:
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
