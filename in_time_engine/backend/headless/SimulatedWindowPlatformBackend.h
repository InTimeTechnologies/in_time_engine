#pragma once

// Dependencies | in_time_engine | window | backend
#include <in_time_engine/window/backend/IWindowPlatformBackend.h>

namespace it {
	class SimulatedWindowPlatformBackend : public IWindowPlatformBackend {
		// Object
		public:
			// Constructor / Destructor
			SimulatedWindowPlatformBackend() = default;

			// Functions
			IWindowBackend* createWindowBackend(Window& owner) override;
			void destroyWindowBackend(IWindowBackend* iWindowBackend) override;
	};
}
