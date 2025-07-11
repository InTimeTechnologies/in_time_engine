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

// Depencies | InTimeEngine
#include "ComponentType.h"
#include "ObjectStatus.h"
#include "MemoryAllocationType.h"

// Forward declarations

namespace it {
	// Forward declarations
	class GameObject;
	class Component;

	class Component {
		// Friends
		friend class GameObject;
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static const ComponentType COMPONENT_TYPE = ComponentType::COMPONENT;
			static std::list<Component*> componentsToDelete;
			static MemoryAllocationType s_currentObjectMemoryAllocationType; // Used by the new function to pass data from it to the object

			// Functions
			static void s_collectGarbage();

			// Object
		private:
			// Properties
			GameObject& gameObject;
			const std::type_info& typeInfo;
			std::list<Component*>::iterator componentNode;
			std::vector<Component*> dependants;
			ObjectStatus status = ObjectStatus::HEALTHY;
			MemoryAllocationType memoryAllocationType = MemoryAllocationType::STACK;

		public:
			// Properties
			bool deleteOnDestroy = true;
			unsigned long long sceneIndex = 0ULL;

			// Constructors / Destructor
			Component(GameObject& gameObject, const std::type_info& typeInfo);
			virtual ~Component();

			// Getters
			GameObject& getGameObject() const;
			const std::type_info& getTypeInfo() const;
			ObjectStatus getStatus() const;
			MemoryAllocationType getMemoryAllocationType() const;
			virtual ComponentType getComponentType() const;

			// Functions
			void destroy();
			void destroyImmediately();

			// Events
			virtual void onMarkForDestroy();
			virtual void onDestroy();

			// Operators
			void* operator new(size_t size);
	};
}
