#include "Box2DVisualizer.h"

// Dependencies | in_time_engine
#include <in_time_engine/physics_engine_2d/PhysicsEngine2D.h>

// class Box2DVisualizer

// Object | public

// Functions
void it::Box2DVisualizer::render() {
	std::list<it::RigidBody2D*> rigidBodies = it::RigidBody2D::s_rigidBodyList;
	size_t rigidBodyCount = rigidBodies.size();

	for (it::RigidBody2D* rigidBody : rigidBodies) {

	}
}
