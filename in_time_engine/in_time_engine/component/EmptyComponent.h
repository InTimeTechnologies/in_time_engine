#pragma once

// Dependencies | InTimeEngine
#include "../InTimeEngine.h"

namespace it {
	class EmptyComponent : public Component {
		public:
			// Constructor / Destructor
			EmptyComponent(GameObject& gameObject) : Component(gameObject, typeid(EmptyComponent)) {};
			~EmptyComponent() = default;

			// Getters
			ComponentType getComponentType() const override {
				return ComponentType::EMPTY_COMPONENT;
			}
	};
}
