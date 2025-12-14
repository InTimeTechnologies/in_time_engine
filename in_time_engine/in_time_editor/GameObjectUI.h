#pragma once

// Dependencies | in_time_engine
#include <in_time_engine/InTimeEngine.h>

namespace it {
	class GameObjectUI {
		// Friends
		friend class InTimeEditor;

		// Object
		private:
			// Properties
			bool isOpen{ false };
			int gameObjectId{ 0 };
			char gameObjectName[128];

		public:
			// Functions
			void update(InTimeEngine& inTimeEngine);
	};
}