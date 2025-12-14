#include "ShapeB2D.h"

// Dependencies | std
#include <cassert>

// Dependencies | physics_engine_2d
#include "../LifeCycleFunctions.h"

namespace it {
	// class ShapeB2D

	// Object | public

	// Getters
	const std::type_info& ShapeB2D::getTypeInfo() const {
		return typeid(ShapeB2D);
	}
	b2ShapeId ShapeB2D::getShapeId() const {
		return id;
	}

	// Functions
	bool ShapeB2D::initShape(b2BodyId bodyId, b2ShapeDef& shapeDef, const b2Polygon& polygon) {
		// Error check
		assert(gameObject != nullptr && "ShapeB2D::initShape(): gameObject == nullptr");
		assert(!b2Shape_IsValid(id) && "ShapeB2D::initShape(): shape already initialized");
		assert(b2Body_GetUserData(bodyId) != nullptr && "ShapeB2D::initShape(): body has no user data");
		if (gameObject == nullptr || b2Shape_IsValid(id) || b2Body_GetUserData(bodyId) == nullptr)
			return false;

		// Create shape and link to game object
		shapeDef.userData = this;
		id = b2CreatePolygonShape(bodyId, &shapeDef, &polygon);
		
		// Succcess
		return true;
	}
	bool ShapeB2D::initShape(b2ShapeId& shapeId) {
		// Error check
		assert(gameObject != nullptr && "ShapeB2D::initShape(): gameObject == nullptr");
		assert(!b2Shape_IsValid(id) && "ShapeB2D::initShape(): this shape already initialized");
		assert(b2Shape_IsValid(shapeId) && "ShapeB2D::initShape(): this shape already initialized");
		assert(b2Shape_GetUserData(shapeId) == nullptr && "ShapeB2D::initShape(): shape already has user data");
		assert(b2Body_GetUserData(b2Shape_GetBody(shapeId)) != nullptr && "ShapeB2D::initShape(): body has no user data");
		assert(b2Body_IsValid(b2Shape_GetBody(shapeId)) && "ShapeB2D::initShape(): shape's body is not valid");
		if (gameObject == nullptr || b2Shape_IsValid(id) || !b2Shape_IsValid(shapeId) || b2Shape_GetUserData(shapeId) != nullptr || b2Body_GetUserData(b2Shape_GetBody(shapeId)) == nullptr || !b2Body_IsValid(b2Shape_GetBody(shapeId)))
			return false;

		// Link to game object
		b2Shape_SetUserData(shapeId, this);
		this->id = shapeId;

		// Success
		return true;
	}
	bool ShapeB2D::shapeInitialized() const {
		return b2Shape_IsValid(id);
	}

	// Events
	void ShapeB2D::onAddToGameObject() {
	
	}
	void ShapeB2D::onMarkForDestroy() {
	
	}
	void ShapeB2D::onDestroy() {
		if (b2Shape_IsValid(id)) {
			// Error check
			PhysicsEngineB2D* engine = PhysicsEngineB2D::s_getSingleton();
			assert(engine != nullptr && "PhysicsEngineB2D singleton == nullptr");

			// Destroy shape
			b2DestroyShape(id, updateMassOnDestroy);
			id = b2_nullShapeId;
		}
	}
}
