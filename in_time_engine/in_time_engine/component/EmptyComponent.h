#pragma once

// Dependencies | InTimeEngine
#include "../Component.h"

namespace it {
	class EmptyComponent : public Component {
		// Object
		public:
			// Getters
			const std::type_info& getTypeInfo() const override {
				return typeid(EmptyComponent);
			}
	};
}
