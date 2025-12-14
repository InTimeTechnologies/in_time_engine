#pragma once

// Dependencies | std
#include <vector>

namespace it {
	// Forward declarations
	class Component;

	class ComponentManager {
		// Freinds
		friend class InTimeEngine;
		friend class GameObjectManager;

		// Object
		private:
			// Properties
			std::vector<Component*> componentsToDelete{};

		public:
			// Functions
			bool destroy(Component& component);
			bool destroyImmediately(Component& component);
			void collectGarbage();
	};
}

