#pragma once

// Dependencies | in_time_engine | window | backend
#include "IWindowPlatformBackend.h"

namespace it {
	class NullWindowPlatformBackend : public IWindowPlatformBackend {
		IWindowBackend* createWindow() override;
		void destroyWindow(IWindowBackend* iWindowBackend) override;
	};
}
