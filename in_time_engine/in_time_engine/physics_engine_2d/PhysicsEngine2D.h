#pragma once

// Dependencies | box2d
#include <box2d/box2d.h>

namespace it {
	class PhysicsEngine2D {
        // Static
        private:
            // Properties
            static PhysicsEngine2D* s_singleton;

        public:
            // Getters
            static PhysicsEngine2D* s_getSingleton();

        // Object
        private:
            // Properties
            b2WorldId id = b2_nullWorldId;
            int subStepCount = 8;

        public:
            // Constructor / Destructor
            PhysicsEngine2D();
            PhysicsEngine2D(const b2WorldDef& worldDefinition);
            PhysicsEngine2D(const PhysicsEngine2D& engine) = delete;
            PhysicsEngine2D(PhysicsEngine2D&& engine) = delete;
            ~PhysicsEngine2D();

            // Assignment operators
            PhysicsEngine2D& operator=(const PhysicsEngine2D& engine) = delete;
            PhysicsEngine2D& operator=(PhysicsEngine2D&& engine) = delete;

            // Getters
            b2WorldId getWorldId() const;
            int getSubStepCount() const;

            // Functions
            void update(float timeStep);
	};
}

// Dependencies | physics_engine_2d
#include "RigidBody2D.h"
#include "Shape2D.h"
