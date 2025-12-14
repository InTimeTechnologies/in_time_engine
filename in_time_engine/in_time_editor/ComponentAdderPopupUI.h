#pragma once

// Dependencies | in_time_engine
#include <in_time_engine/InTimeEngine.h>

namespace it {
	class ComponentAdderPopupUI {
		// Friends
		friend class InspectorUI;

		private:
			// Properties
			bool isOpen{ false };

		public:
			// Functions
			void update(GameObject& gameObject);
	};
}