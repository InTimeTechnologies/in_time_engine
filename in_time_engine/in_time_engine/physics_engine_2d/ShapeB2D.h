#pragma once

// Dependencies | in_time_engine
#include "../Component.h"

// Dependencies | box2d
#include <box2d/box2d.h>

namespace it {
	class ShapeB2D : public Component {
		// Friends
		friend class RigidBodyB2D;

		// Object
		private:
			// Properties
			b2ShapeId id{ b2_nullShapeId };
			bool updateMassOnDestroy{ true };

		public:
			// Getters
			const std::type_info& getTypeInfo() const override;
			b2ShapeId getShapeId() const;

			// Functions
			bool initShape(b2BodyId bodyId, b2ShapeDef& shapeDef, const b2Polygon& polygon);
			bool initShape(b2ShapeId& shapeId);
			bool shapeInitialized() const;

			// Events
			void onAddToGameObject() override;
			void onMarkForDestroy() override;
			void onDestroy() override;
	};
}
