#pragma once

// Dependencies | in_time_editor
#include "HierarchyUI.h"
#include "InspectorUI.h"

namespace it {
	class InTimeEditor {
		// Static
		private:
			// Properties
			static InTimeEditor* singleton;

		public:
			// Getters
			static InTimeEditor* getSingleton();

		// Object
		public:
			// Properties
			HierarchyUI hierarchy = HierarchyUI();
			InspectorUI inspector = InspectorUI();

			// Constructor / Destructor
			InTimeEditor();
			~InTimeEditor();

			// Functions
			void update();
	};
}
