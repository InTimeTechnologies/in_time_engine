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
 * File: GameObject.h
 * Author: Christopher Barrios Agosto
 * Created on: 13DEC2024
 *
 * Description:
 *  Serves as a container for components created by the user. It has a
 *  transorm object that the user can use, but so as the physics and rendering
 *  system.
 *  Calling destroy or destroyImmediately will unlink the game object from the
 *  engine.
 *****************************************************************************/

#pragma once

// Dependencies | std
#include <string>
#include <typeinfo>
#include <vector>
#include <list>
#include <memory>

// Dependencies | in_time_engine
#include "ObjectStatus.h"
#include "Transform.h"
#include "Component.h"

// Forward declarations
namespace it {
	// Forward declarations
	class GameObjectManager;
	class GameObject;
	class Component;
	class InTimeEngine;

	class GameObject {
		// Friends
		friend class InTimeEngine;
		friend class Component;
		friend class GameObjectManager;
		friend class ComponentManager;
		friend class Scene;

		// Object
		private:
			// Properties
			std::list<GameObject>::iterator node{};
			ObjectStatus status{ ObjectStatus::HEALTHY };
			std::vector<Component*> components{};
			std::shared_ptr<GameObject*> selfSharedPointer{ std::make_shared<GameObject*>(this) };

		public:
			// Properties
			int id{};
			std::string name{};
			Transform transform{ this };

			// Constructors / Dsetructor
			GameObject();
			GameObject(const std::string& name);
			GameObject(int id);
			GameObject(int id, const std::string& name);

		public:
			// Getters
			ObjectStatus getStatus() const;
			std::weak_ptr<GameObject*> getWeakPointer();

			// Functions | Component
			Component& addComponent(Component* component);

			long long getNumberOfComponents() const;
			std::vector<Component*> getComponents() const;
			std::vector<Component*> getComponents(const std::type_info& typeInfo) const;
			Component* getComponent(const std::type_info& typeInfo) const;
			Component* getFirstComponent() const;
			Component* getLastComponent() const;
			int getComponentIndex(Component* component) const;
	};
}