// Dependencies | UI
#include <ui_engine/UI.h>

// Dependencies | std
#include <string>
#include <iostream>

// Dependencies | in_time_engine
#include <in_time_engine/GameObject.h>

namespace it {
	class HierarchyUI {
		// Object
		private:
			// Functions
			void processHiararchy(const Transform& transform);

		public:
			// Properties
			std::vector<Transform*> transforms = std::vector<Transform*>(0);

			// Constructor / Destructor
			HierarchyUI() = default;
			~HierarchyUI() = default;

			// Functions
			void update();
	};
}
