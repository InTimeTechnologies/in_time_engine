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

// GameObject

// Static | private

// Properties
it::MemoryAllocationType it::GameObject::s_currentObjectMemoryAllocationType = it::MemoryAllocationType::STACK;

// Functions
void it::GameObject::s_collectGarbage() {
	// Note: A while loop is used because deleting a game object can cause other game objects to be deleted
	// Do not replace with any other type of loop
	// Do not replace std::list for s_gameObjectsToDeleteList with any other data structures. New game objects to be deleted must be added to the back, not the front
	while (s_gameObjectsToDeleteList.size() > 0) {
		GameObject* gameObject = s_gameObjectsToDeleteList.front();
		s_gameObjectsToDeleteList.pop_front();
		gameObject->status = ObjectStatus::DESTROYED;

		s_gameObjectList.erase(gameObject->node);
		
		if (gameObject->deleteOnDestroy && gameObject->memoryAllocationType == MemoryAllocationType::HEAP)
			delete(gameObject);
	}
}

// Static | public

// Properties | System
std::list<it::GameObject*> it::GameObject::s_gameObjectList = std::list<it::GameObject*>();
std::list<it::GameObject*> it::GameObject::s_gameObjectsToDeleteList = std::list<it::GameObject*>();

// Properties | Default values
int it::GameObject::s_defaultId = 0;
std::string it::GameObject::s_defaultName = "Game Object";

// Functions
void it::GameObject::s_destroyGameObjects() {
	for (GameObject* gameObject : s_gameObjectList)
		gameObject->destroy();
}
void it::GameObject::s_destroyGameObjectsImmediately() {
	while (s_gameObjectList.size() > 0) {
		GameObject* gameObject = s_gameObjectList.front();
		gameObject->destroyImmediately();
	}
}

// Object | public

// Constructors / Destructor
it::GameObject::GameObject() : GameObject(GameObject::s_defaultId, GameObject::s_defaultName) {

}
it::GameObject::GameObject(std::string name) : GameObject(GameObject::s_defaultId, name) {

}
it::GameObject::GameObject(int id) : GameObject(id, GameObject::s_defaultName) {

}
// This is the contructor that the other ones call
it::GameObject::GameObject(int id, const std::string& name) :  id(id), name(name) {
	s_gameObjectList.push_back(this);
	node = std::prev(s_gameObjectList.end());

	if (s_currentObjectMemoryAllocationType == MemoryAllocationType::HEAP) {
		memoryAllocationType = s_currentObjectMemoryAllocationType;
		s_currentObjectMemoryAllocationType = MemoryAllocationType::STACK;
	}
}
it::GameObject::~GameObject() {
	deleteOnDestroy = false;
	if (status != ObjectStatus::DESTROYED)
		destroyImmediately();
}

// Object | public

// Getters
it::ObjectStatus it::GameObject::getStatus() const {
	return status;
}
it::MemoryAllocationType it::GameObject::getMemoryAllocationType() const {
	return memoryAllocationType;
}

// Functions
void it::GameObject::destroy() {
	// If a lready marked for deletion or is already deleted, return
	if (status != ObjectStatus::HEALTHY)
		return;

	// Mark game object for deletion
	s_gameObjectsToDeleteList.push_back(this);
	status = ObjectStatus::MARKED_FOR_DESTROY;

	// Notify components that game object is marked for deletion
	for (Component* component : components)
		component->destroy();
}
void it::GameObject::destroyImmediately() {
	// Destroy each component attached to this game object immediately
	while (components.size() > 0)
		components.front()->destroyImmediately();

	// If this game object is currently marked for deletion, remove it from the list
	if (status == ObjectStatus::MARKED_FOR_DESTROY)
		s_gameObjectsToDeleteList.remove(this);

	s_gameObjectList.erase(node);
	status = ObjectStatus::DESTROYED;
	if (deleteOnDestroy && memoryAllocationType == MemoryAllocationType::HEAP)
		delete(this);
}

// Functions | Component
long long it::GameObject::getNumberOfComponents() const {
	return components.size();
}
std::vector<it::Component*> it::GameObject::getComponents() const {
	std::vector<Component*> components = std::vector<Component*>();

	for (Component* component : this->components)
		if (component->status == ObjectStatus::HEALTHY)
			components.push_back(component);

	return components;
}
std::vector<it::Component*> it::GameObject::getComponents(const std::type_info& typeInfo) const {
	std::vector<Component*> components = std::vector<Component*>();

	for (Component* component : this->components)
		if (component->status == ObjectStatus::HEALTHY && typeInfo == component->typeInfo)
			components.push_back(component);

	return components;
}
it::Component* it::GameObject::getComponent(const std::type_info& typeInfo) const {
	// Match typeInfo to any component attached to this game object
	for (Component* component : components)
		if (component->getTypeInfo() == typeInfo && component->status == ObjectStatus::HEALTHY)
			return component; // Return matched component

	// Did not match give typeInfo to any of the components in the game object
	return nullptr;
}
it::Component* it::GameObject::getFirstComponent() const {
	if (components.size() == 0)
		return nullptr;

	return components.front();
}
it::Component* it::GameObject::getLastComponent() const {
	if (components.size() == 0)
		return nullptr;

	return components.back();
}
int it::GameObject::getComponentIndex(Component* component) const {
	int i = 0;
	for (Component* currentComponent : components) {
		if (currentComponent == component)
			return i;
		i++;
	}
	return -1;
}

// Operators
void* it::GameObject::operator new(size_t size) {
	s_currentObjectMemoryAllocationType = MemoryAllocationType::HEAP;
	return ::operator new(size);
}
