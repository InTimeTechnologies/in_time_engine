#pragma once

// Dependencies | box2d
#include <box2d/box2d.h>

// Dependencies | gl_engine
#include <gl_engine/GLEngine.h>

namespace it {
	class Box2DVisualizer {
		// Object
		public:
			// Properties
			b2WorldId worldId = b2_nullWorldId;

			// Constructor / Destructor
			Box2DVisualizer() = default;
			Box2DVisualizer(const Box2DVisualizer& other) = default;
			~Box2DVisualizer() = default;

			// Operator | assignment
			Box2DVisualizer& operator=(const Box2DVisualizer& other) = default;
			Box2DVisualizer& operator=(Box2DVisualizer&& other) = default;

			// Functions
			void render();
	};
}
