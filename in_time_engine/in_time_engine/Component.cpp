/******************************************************************************
 * Copyright (c) 2024 Christopher Barrios Agosto. All Rights Reserved.
 *
 * Licensing Information:
 *  This software and associated documentation files (the "Software") may not
 *  be used, copied, modified, merged, published, distributed, sublicensed,
 *  or sold without the prior written permission of the copyright owner.
 *
 *  Unauthorized use of this file, via any medium, is strictly prohibited.
 *****************************************************************************/

/******************************************************************************
 * Project: In Time Engine
 * File: Component.cpp
 * Author: Christopher Barrios Agosto
 * Created on: 13DEC2024
 *
 * Description:
 *  This is what gives functionality to whatever game object it is attached to
 *  and is meant to be overriden by user defined classes. It can be stack or
 *  heap allocated. Memory management relies on the user. Calling destroy or
 *  destroyImmediately will unlink the component from the game engine. You can
 *  get notified of when destruction happens by overriding onMarkForDestroy
 *  and onDestroy.
 *****************************************************************************/

#include "Component.h"

namespace it {
	// Component

	// Object | protected
	Component::~Component() {

	}

	// Object | public

	// Getters
	GameObject* Component::getGameObject() const {
		return gameObject;
	}
	ObjectStatus Component::getStatus() const {
		return status;
	}
	std::weak_ptr<Component*> Component::getWeakPointer() {
		return selfSharedPointer;
	}

	// Events
	void Component::onAddToGameObject() {
		// To be implemented in child class
	}
	void Component::onMarkForDestroy() {
		// To be implemented in child class
	}
	void Component::onDestroy() {
		// To be implemented in child class
	}
}

