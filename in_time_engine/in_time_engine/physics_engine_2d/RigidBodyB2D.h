#pragma once

// Dependencies | in_time_engine
#include "../Component.h"

// Dependencies | box2d
#include <box2d/box2d.h>

namespace it {
	class RigidBodyB2D : public Component {
		// Object
		private:
			// Properties
			b2BodyId id{ b2_nullBodyId };

		public:
			// Getters
			const std::type_info& getTypeInfo() const override;
			b2BodyId getId() const;

			// Functions
			bool initBody(b2BodyDef& bodyDef);
			bool initBody(b2BodyId& id);

			// Events
			void onAddToGameObject() override;
			void onMarkForDestroy() override;
			void onDestroy() override;
	};
}
