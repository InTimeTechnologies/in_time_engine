#pragma once

#include "RigidBody2D.h"

// Dependencies | std
#include <cassert>

// Dependencies | in_time_engine
#include "../GameObject.h"
#include "PhysicsEngine2D.h"
#include "Shape2D.h"

// class RigidBody2D

// Static | public

// Properties
std::list<it::RigidBody2D*> it::RigidBody2D::s_rigidBodyList = std::list<it::RigidBody2D*>();

// Object | public

// Constructor / Destructor
it::RigidBody2D::RigidBody2D(it::GameObject& gameObject, b2BodyDef& bodyDefinition) : Component(gameObject, typeid(RigidBody2D)), id(id) {
	// Get physics engine and its world id
	PhysicsEngine2D* physicsEngine2D = PhysicsEngine2D::s_getSingleton();
	assert(physicsEngine2D != nullptr);
	b2WorldId worldId = physicsEngine2D->getWorldId();

	// Copy game object's transform to rigid body 2D, associate it with its game object and create it
	Transform& transform = gameObject.transform;
	bodyDefinition.position.x = transform.position.x;
	bodyDefinition.position.y = transform.position.y;
	bodyDefinition.rotation = b2MakeRot(transform.getGlobalRotation().z);
	bodyDefinition.userData = this;
	id = b2CreateBody(worldId, &bodyDefinition);

	// Push rigid body 2D to the static list
	s_rigidBodyList.push_back(this);
	node = std::prev(s_rigidBodyList.end());

	// Link rigid body to transform
	transform.rigidBody2D = this;
}
it::RigidBody2D::RigidBody2D(it::GameObject& gameObject, b2BodyId id) : Component(gameObject, typeid(RigidBody2D)), id(id) {
	// Copy game object's transform to rigid body 2D and associate it with its game object
	Transform& transform = gameObject.transform;
	b2Body_SetTransform(id, b2Vec2{ transform.position.x, transform.position.y }, b2MakeRot(transform.getGlobalRotation().z));
	b2Body_SetUserData(id, &gameObject);

	// Push rigid body 2D to the static list
	s_rigidBodyList.push_back(this);
	node = std::prev(s_rigidBodyList.end());

	// Link rigid body to transform
	transform.rigidBody2D = this;
}

// Getters
b2BodyId it::RigidBody2D::getId() const {
	return id;
}

// Funcitons | Component
void it::RigidBody2D::onDestroy() {
	// Get all the components of the game object
	std::vector<Component*> components = getGameObject().getComponents();

	// Destroy immediately any shape associated with this rigid body
	for (Component* component : components)
		if (component->getTypeInfo() == typeid(Shape2D))
			((RigidBody2D*)component)->destroyImmediately();

	// Destroy box2d rigid body
	b2DestroyBody(id);
	s_rigidBodyList.erase(node);

	Transform& transform = getGameObject().transform;
	transform.rigidBody2D = nullptr;
}
