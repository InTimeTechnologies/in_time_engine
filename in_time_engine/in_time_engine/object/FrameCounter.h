#pragma once

// Dependencies | std
#include <iostream>

// Dependencies | in_time_engine
#include "../InTimeEngine.h"

namespace it {
	class FrameCounter : public UpdateEvent, public PhysicsUpdateEvent2D {
		// Object
		private:
			// Properties
			size_t updateFrameCount = 0ULL;
			size_t physicsUpdateFrameCount = 0ULL;
			std::chrono::nanoseconds nextCoreUpdateTime = InTimeEngine::s_getSingleton()->coreTime.getTime() + std::chrono::seconds(1);
			std::chrono::nanoseconds nextPhysicsUpdateTime = InTimeEngine::s_getSingleton()->physicsTime.getTime() + std::chrono::seconds(1);

		public:
			// Properties
			bool printToConsole = true;

			// Constructor / Destructor
			FrameCounter() = default;
			~FrameCounter() = default;

			// Functions
			void onPreUpdate() override {
				InTimeEngine* inTimeEngine = InTimeEngine::s_getSingleton();
				Time& time = inTimeEngine->coreTime;
				updateFrameCount++;

				if (time.getTime() >= nextCoreUpdateTime) {
					// Print frame count to console
					std::cout << "\tupdate frames:  " << updateFrameCount << std::endl;

					// Set next update time
					nextCoreUpdateTime += std::chrono::seconds(1);

					// Reset counter
					updateFrameCount = 0ULL;
				}
			}
			void onPrePhysicsUpdate2D() {
				InTimeEngine* inTimeEngine = InTimeEngine::s_getSingleton();
				Time& physicsTime = inTimeEngine->physicsTime;
				physicsUpdateFrameCount++;

				if (physicsTime.getTime() >= nextPhysicsUpdateTime) {
					std::cout << "\tphysics frames: " << physicsUpdateFrameCount << std::endl;

					// Set next update time
					nextPhysicsUpdateTime += std::chrono::seconds(1);

					// Reset counter
					physicsUpdateFrameCount = 0ULL;
				}
			}
	};
}
