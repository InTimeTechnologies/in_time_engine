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

#include "GameObject.h"

// Dependencies | CoreEngine
#include "Component.h"

namespace it {
	// class GameObject

	// Object | public

	// Constructors / Destructor
	GameObject::GameObject() {

	}
	GameObject::GameObject(const std::string& name) : name(name) {

	}
	GameObject::GameObject(int id) : id(id) {

	}
	// This is the contructor that the other ones call
	GameObject::GameObject(int id, const std::string& name) : id(id), name(name) {
		
	}

	// Object | public

	// Getters
	ObjectStatus GameObject::getStatus() const {
		return status;
	}
	std::weak_ptr<GameObject*> GameObject::getWeakPointer() {
		return selfSharedPointer;
	}

	// Functions | Component
	Component& GameObject::addComponent(Component* component) {
		components.push_back(component);
		component->gameObject = this;
		component->onAddToGameObject();
		return *component;
	}
	std::vector<Component*> GameObject::getComponents() const {
		std::vector<Component*> components = std::vector<Component*>();

		for (Component* component : this->components)
			if (component->status == ObjectStatus::HEALTHY)
				components.push_back(component);

		return components;
	}
	std::vector<Component*> GameObject::getComponents(const std::type_info& typeInfo) const {
		std::vector<Component*> components = std::vector<Component*>();

		for (Component* component : this->components)
			if (component->status == ObjectStatus::HEALTHY && typeInfo == component->getTypeInfo())
				components.push_back(component);

		return components;
	}
	Component* GameObject::getComponent(const std::type_info& typeInfo) const {
		// Match typeInfo to any component attached to this game object
		for (Component* component : components)
			if (component->getTypeInfo() == typeInfo && component->status == ObjectStatus::HEALTHY)
				return component; // Return matched component

		// Did not match give typeInfo to any of the components in the game object
		return nullptr;
	}
	Component* GameObject::getFirstComponent() const {
		if (components.size() == 0)
			return nullptr;

		return components.front();
	}
	Component* GameObject::getLastComponent() const {
		if (components.size() == 0)
			return nullptr;

		return components.back();
	}
	int GameObject::getComponentIndex(Component* component) const {
		int i = 0;
		for (Component* currentComponent : components) {
			if (currentComponent == component)
				return i;
			i++;
		}
		return -1;
	}
}
