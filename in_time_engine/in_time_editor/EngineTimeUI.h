#pragma once

// Dependencies | in_time_engine
#include <in_time_engine/InTimeEngine.h>

namespace it {
	class EngineTimeUI {
		// Freinds
		friend class InTimeEditor;

		// Object
		public:
			// Properties
			bool isOpen{ false };

			// Functions
			void update(InTimeEngine& inTimeEngine);

		private:
			// Functions
			double toSeconds(std::chrono::nanoseconds nanoseconds);
			void renderTime(RealTime& realTime);
			void renderTime(Time& time);
			void renderFixedTime(FixedTime& fixedTime);
	};
}
