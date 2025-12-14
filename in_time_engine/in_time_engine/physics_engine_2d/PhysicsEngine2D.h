#pragma once

// Dependencies | box2d
#include <box2d/box2d.h>

namespace it {
	class PhysicsEngineB2D {
        // Static
        private:
            // Properties
            static PhysicsEngineB2D* s_singleton;

        public:
            // Getters
            static PhysicsEngineB2D* s_getSingleton();


        // Object
        private:
            // Properties
            b2WorldId id = b2_nullWorldId;
            int subStepCount = 8;

        public:
            // Constructor / Destructor
            PhysicsEngineB2D();
            PhysicsEngineB2D(const b2WorldDef& worldDefinition);
            PhysicsEngineB2D(const PhysicsEngineB2D& engine) = delete;
            PhysicsEngineB2D(PhysicsEngineB2D&& engine) = delete;
            ~PhysicsEngineB2D();

            // Assignment operators
            PhysicsEngineB2D& operator=(const PhysicsEngineB2D& engine) = delete;
            PhysicsEngineB2D& operator=(PhysicsEngineB2D&& engine) = delete;

            // Getters
            b2WorldId getWorldId() const;
            int getSubStepCount() const;

            // Functions
            void update(float timeStep);
	};
}

// Dependencies | physics_engine_2d
#include "RigidBodyB2D.h"
#include "ShapeB2D.h"

