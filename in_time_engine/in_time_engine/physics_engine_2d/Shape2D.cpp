#include "Shape2D.h"

// Dependencies | in_time_engine
#include "../GameObject.h"

// Dependencies | physics_engine_2d
#include "RigidBody2D.h"

// class Shape2D

// Object | private

// Functions
bool it::Shape2D::gameObjectHasRigidBody2D() {
	Component* rigidBody2D = getGameObject().getComponent(typeid(RigidBody2D));
	return rigidBody2D != nullptr;
}

// Object | public

// Constructor / Destructor
it::Shape2D::Shape2D(it::GameObject& gameObject, b2ShapeDef& shapeDefinition, b2Polygon& polygon) : Component(gameObject, typeid(Shape2D)) {
	RigidBody2D* rigidBody2D = (RigidBody2D*)gameObject.getComponent(typeid(RigidBody2D));
	assert(rigidBody2D != nullptr);

	shapeDefinition.userData = &gameObject;
	id = b2CreatePolygonShape(rigidBody2D->getId(), &shapeDefinition, &polygon);
}
it::Shape2D::Shape2D(it::GameObject& gameObject, b2ShapeId shapeId) : Component(gameObject, typeid(Shape2D)) {
	assert(gameObjectHasRigidBody2D());

	id = shapeId;
	b2Shape_SetUserData(id, this);
}
it::Shape2D::~Shape2D() {
	b2DestroyShape(id, updateMassOnDestroy);
}

// Getters
b2ShapeId it::Shape2D::getId() const {
	return id;
}
