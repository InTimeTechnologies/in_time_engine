#pragma once

// Dependencies | in_time_engine | window | backend
#include "IWindowPlatformBackend.h"

namespace it {
	class SimulatedWindowPlatformBackend : public IWindowPlatformBackend {
		// Object
		public:
			// Properties
			IWindowBackend* windowBackend{ nullptr };

			// Functions
			IWindowBackend* createWindow() override;
			void destroyWindow(IWindowBackend* iWindowBackend) override;
	};
}
