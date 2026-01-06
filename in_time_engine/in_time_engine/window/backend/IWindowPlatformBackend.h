#pragma once

// Dependencies | in_time_engine
#include "IWindowBackend.h"

namespace it {
	// Forward declarations
	class Window;

	class IWindowPlatformBackend {
		// Object
		public:
			// Functions
			virtual IWindowBackend* createWindowBackend(Window& owner) = 0;
			virtual void destroyWindowBackend(IWindowBackend* iWindowBackend) = 0;
	};
}
