#include "PhysicsEngine2D.h"

// class PhysicsEngine2D

// Static | private

// Properties
it::PhysicsEngine2D* it::PhysicsEngine2D::s_singleton = nullptr;

// Static | public
it::PhysicsEngine2D* it::PhysicsEngine2D::s_getSingleton() {
    return s_singleton;
}

// Object | public

// Constructor / Destructor
it::PhysicsEngine2D::PhysicsEngine2D() {
    // Create world
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity.y = -10.0f;
    id = b2CreateWorld(&worldDef);

    // Set singleton
    if (s_singleton == nullptr)
        s_singleton = this;
}
it::PhysicsEngine2D::PhysicsEngine2D(const b2WorldDef& worldDefinition) {
    // Create world
    id = b2CreateWorld(&worldDefinition);

    if (s_singleton == nullptr)
        s_singleton = this;
}
it::PhysicsEngine2D::~PhysicsEngine2D() {
    // Destroy world
    b2DestroyWorld(id);
    id = b2_nullWorldId;

    // Unset singleton
    if (s_singleton == this)
        s_singleton = nullptr;
}

// Getters
b2WorldId it::PhysicsEngine2D::getWorldId() const {
    return id;
}
int it::PhysicsEngine2D::getSubStepCount() const {
    return subStepCount;
}

// Functions
void it::PhysicsEngine2D::update(float timeStep) {
    b2World_Step(id, timeStep, subStepCount);
}
