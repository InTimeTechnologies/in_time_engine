#include "RigidBodyB2D.h"

// Dependencies | std
#include <cassert>

// Dependencies | physics_engine_2d
#include "PhysicsEngine2D.h"
#include "ShapeB2D.h"

// Dependencies | in_time_engine
#include "../LifeCycleFunctions.h"

namespace it {
	// class RigidBodyB2D

	// Object | public

	// Getters
	const std::type_info& RigidBodyB2D::getTypeInfo() const {
		return typeid(RigidBodyB2D);
	}
	b2BodyId RigidBodyB2D::getId() const {
		return id;
	}

	// Functions
	bool RigidBodyB2D::initBody(b2BodyDef& bodyDef) {
		// Error check
		assert(gameObject != nullptr && "RigidBodyB2D::initBody(): gameObject == nullptr");
		assert(!b2Body_IsValid(id) && "RigidBodyB2D::initBody(): body already initialized");
		if (gameObject == nullptr || b2Body_IsValid(id))
			return false;

		// Create body and link to game object
		PhysicsEngineB2D* engine = PhysicsEngineB2D::s_getSingleton();
		assert(engine != nullptr && "PhysicsEngineB2D singleton == nullptr");
		bodyDef.userData = this;
		id = b2CreateBody(engine->getWorldId(), &bodyDef);

		// Success
		return true;
	}
	bool RigidBodyB2D::initBody(b2BodyId& bodyId) {
		// Error check
		assert(gameObject != nullptr && "RigidBodyB2D::initBody(): gameObject == nullptr");
		assert(!b2Body_IsValid(id) && "RigidBodyB2D::initBody(): body already initialized");
		assert(b2Body_GetUserData(bodyId) == nullptr && "RigidBodyB2D::initBody(): body already has user data");
		if (gameObject == nullptr || b2Body_IsValid(id) || b2Body_GetUserData(bodyId) != nullptr)
			return false;

		// Link to game object
		b2Body_SetUserData(bodyId, this);
		this->id = bodyId;

		// Success
		return true;
	}

	// Events
	void RigidBodyB2D::onAddToGameObject() {

	}
	void RigidBodyB2D::onMarkForDestroy() {

	}
	void RigidBodyB2D::onDestroy() {
		// Error check
		assert(b2Body_IsValid(id) && "RigidBodyB2D::onDestroy(): body not initialized");
		if (!b2Body_IsValid(id))
			return;

		// Unlink shapes from their respective ShapeB2D components and destroy their components
		int shapeCount = b2Body_GetShapeCount(id);
		b2ShapeId* shapeIds = new b2ShapeId[shapeCount];
		b2Body_GetShapes(id, shapeIds, shapeCount);
		for (int i = 0; i < shapeCount; i++) {
			b2ShapeId shapeId = shapeIds[i];
			ShapeB2D* shapeComponent = reinterpret_cast<ShapeB2D*>(b2Shape_GetUserData(shapeId));
			b2Shape_SetUserData(shapeId, nullptr);
			if (shapeComponent != nullptr) {
				shapeComponent->id = b2_nullShapeId;
				destroy(*shapeComponent);
			}
		}
		delete[] shapeIds;

		// Destroy box2d body
		b2DestroyBody(id);
		id = b2_nullBodyId;
	}
}
