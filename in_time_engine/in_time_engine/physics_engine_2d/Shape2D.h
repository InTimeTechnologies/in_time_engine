#pragma once

// Dependencies | std
#include <list>

// Dependencies | box2d
#include <box2d/box2d.h>

// Dependencies | in_time_engine
#include "../Component.h"

namespace it {
	class Shape2D : public Component {
		// Object
		private:
			// Properties
			b2ShapeId id = b2_nullShapeId;

			// Functions
			bool gameObjectHasRigidBody2D();

		public:
			// Properties
			bool updateMassOnDestroy = false;

			// Constructor / Destructor
			Shape2D(GameObject& gameObject, b2ShapeDef& shapeDefinition, b2Polygon& polygon);
			Shape2D(GameObject& gameObject, b2ShapeId shapeId);
			~Shape2D();

			// Getters
			b2ShapeId getId() const;
	};
}
