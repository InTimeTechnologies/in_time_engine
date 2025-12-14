#include "PhysicsEngine2D.h"

namespace it {
    // class PhysicsEngineB2D

    // Static | private

    // Properties
    PhysicsEngineB2D* PhysicsEngineB2D::s_singleton = nullptr;

    // Static | public
    PhysicsEngineB2D* PhysicsEngineB2D::s_getSingleton() {
        return s_singleton;
    }

    // Object | public

    // Constructor / Destructor
    PhysicsEngineB2D::PhysicsEngineB2D() {
        // Create world
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity.y = -10.0f;
        id = b2CreateWorld(&worldDef);

        // Set singleton
        if (s_singleton == nullptr)
            s_singleton = this;
    }
    PhysicsEngineB2D::PhysicsEngineB2D(const b2WorldDef& worldDefinition) {
        // Create world
        id = b2CreateWorld(&worldDefinition);

        if (s_singleton == nullptr)
            s_singleton = this;
    }
    PhysicsEngineB2D::~PhysicsEngineB2D() {
        // Destroy world
        b2DestroyWorld(id);
        id = b2_nullWorldId;

        // Unset singleton
        if (s_singleton == this)
            s_singleton = nullptr;
    }

    // Getters
    b2WorldId PhysicsEngineB2D::getWorldId() const {
        return id;
    }
    int PhysicsEngineB2D::getSubStepCount() const {
        return subStepCount;
    }

    // Functions
    void PhysicsEngineB2D::update(float timeStep) {
        b2World_Step(id, timeStep, subStepCount);
    }
}
