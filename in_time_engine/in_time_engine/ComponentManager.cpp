#include "ComponentManager.h"

// Dependencies | std
#include <algorithm>

// Dependencies | in_time_engine
#include "Component.h"
#include "GameObject.h"

namespace it {
	// class ComponentManager

	// Object | public

	// Functions
	bool ComponentManager::destroy(Component& component) {
		if (component.gameObject == nullptr)
			return false;

		switch (component.status) {
			case ObjectStatus::HEALTHY:
				component.onDestroy();
				componentsToDelete.push_back(&component);
				component.status = ObjectStatus::MARKED_FOR_DESTROY;
				return true;
			case ObjectStatus::MARKED_FOR_DESTROY:
				return true;
			case ObjectStatus::DESTROYED:
			case ObjectStatus::UNKNOWN:
			default:
				return false;
		}
	}
	bool ComponentManager::destroyImmediately(Component& component) {
		// Error check
		if (component.gameObject == nullptr || component.status == ObjectStatus::DESTROYED)
			return false;

		// If previously marked for deletion, remove it from the queue
		if (component.status == ObjectStatus::MARKED_FOR_DESTROY) {
			std::vector<Component*>::iterator iterator = std::find(componentsToDelete.begin(), componentsToDelete.end(), &component);
			if (iterator == componentsToDelete.end())
				return false;
			componentsToDelete.erase(iterator);
		}

		// Remove component from its game object
		GameObject* gameObject = component.gameObject;
		std::vector<Component*>& components = gameObject->components;
		std::vector<Component*>::iterator iterator = std::find(components.begin(), components.end(), &component);
		if (iterator != components.end())
			components.erase(iterator);
		component.gameObject = nullptr;

		// Free component memory
		component.status = ObjectStatus::DESTROYED;
		delete &component;
		return true;
	}
	void ComponentManager::collectGarbage() {
		for (Component* component : componentsToDelete) {
			GameObject* gameObject = component->gameObject;
			if (gameObject == nullptr)
				continue;

			std::vector<Component*>& components = gameObject->components;
			std::vector<Component*>::iterator iterator = std::find(components.begin(), components.end(), component);
			if (iterator == components.end())
				continue;
			components.erase(iterator);
			component->gameObject = nullptr;

			component->status = ObjectStatus::DESTROYED;
			delete component;
		}
		
		componentsToDelete.clear();
	}
}
