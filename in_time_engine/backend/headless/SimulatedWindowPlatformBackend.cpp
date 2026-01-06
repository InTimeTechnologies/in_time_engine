#include "SimulatedWindowPlatformBackend.h"

// Dependencies | std
#include <cassert>

// Dependencies | in_time_engine | backend
#include "SimulatedWindowBackend.h"

namespace it {
	// class SimulatedWindowPlatformBackend

	// Object | public

	// Functions | IWindowPlatformBackend
	IWindowBackend* SimulatedWindowPlatformBackend::createWindowBackend(Window& owner) {
		SimulatedWindowBackend* platformBackend = new SimulatedWindowBackend(owner);
		return platformBackend;
	}
	void SimulatedWindowPlatformBackend::destroyWindowBackend(IWindowBackend* iWindowBackend) {
		assert(iWindowBackend != nullptr && "iWindowBackend == nullptr");
		delete iWindowBackend;
	}

}