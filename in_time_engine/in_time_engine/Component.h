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
 * File: Component.h
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

#pragma once

// Dependencies | std
#include <typeinfo>
#include <vector>
#include <list>
#include <memory>

// Depencies | InTimeEngine
#include "ObjectStatus.h"

namespace it {
	// Forward declarations
	class GameObject;

	class Component {
		// Friends
		friend class GameObject;
		friend class GameObjectManager;
		friend class ComponentManager;
		friend class InTimeEngine;
		friend class Scene;

		// Object
		protected:
			// Properties
			GameObject* gameObject{ nullptr };
			ObjectStatus status{ ObjectStatus::HEALTHY };
			std::shared_ptr<Component*> selfSharedPointer{ std::make_shared<Component*>(this) };

		public:
			// Properties
			unsigned long long sceneIndex{ 0ULL };

		protected:
			// Constructor / Destructor
			virtual ~Component();

		public:
			// Getters
			GameObject* getGameObject() const;
			virtual const std::type_info& getTypeInfo() const = 0;
			ObjectStatus getStatus() const;
			std::weak_ptr<Component*> getWeakPointer();

			// Events
			virtual void onAddToGameObject();
			virtual void onMarkForDestroy();
			virtual void onDestroy();
	};
}
