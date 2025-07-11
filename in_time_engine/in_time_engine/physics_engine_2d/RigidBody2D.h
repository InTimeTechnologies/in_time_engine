#pragma once

// Dependencies | std
#include <list>

// Dependencies | box2d
#include <box2d/box2d.h>

// Dependencies | in_time_engine
#include "../Component.h"

namespace it {
	class RigidBody2D : public Component {
		// Friends
		friend class InTimeEngine;

		// Static
		public:
			// Properties
			static std::list<RigidBody2D*> s_rigidBodyList;

		// Object
		private:
			// Properties
			std::list<RigidBody2D*>::iterator node;
			b2BodyId id = b2_nullBodyId;

		public:
			// Constructor / Destructor
			RigidBody2D(GameObject& gameObject, b2BodyDef& bodyDefinition);
			RigidBody2D(GameObject& gameObject, b2BodyId bodyId);
			~RigidBody2D() = default;

			// Getters
			b2BodyId getId() const;

			// Functions | Component
			void onDestroy() override;
	};
}
