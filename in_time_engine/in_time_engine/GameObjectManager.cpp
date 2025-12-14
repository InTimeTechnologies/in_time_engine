#include "GameObjectManager.h"

// Dependencies | in_time_engine
#include "Component.h"

namespace it {
	// class GameObjectManager

	// Object | public

	// Constructor / Destructor
	GameObjectManager::~GameObjectManager() {
		for (GameObject& gameObject : gameObjects)
			destroy(gameObject);
	}

	// Functions
	GameObject& GameObjectManager::createGameObject() {
		GameObject& gameObject = gameObjects.emplace_back(defaultId, defaultName);
		gameObject.node = std::prev(gameObjects.end());
		return gameObject;
	}
	GameObject& GameObjectManager::createGameObject(int id) {
		GameObject& gameObject = gameObjects.emplace_back(id, defaultName);
		gameObject.node = std::prev(gameObjects.end());
		return gameObject;
	}
	GameObject& GameObjectManager::createGameObject(const std::string& name) {
		GameObject& gameObject = gameObjects.emplace_back(defaultId, name);
		gameObject.node = std::prev(gameObjects.end());
		return gameObject;
	}
	GameObject& GameObjectManager::createGameObject(int id, const std::string& name) {
		GameObject& gameObject = gameObjects.emplace_back(id, name);
		gameObject.node = std::prev(gameObjects.end());
		return gameObject;
	}
	void GameObjectManager::destroy(GameObject& gameObject) {
		// If a lready marked for deletion or is already deleted, return
		if (gameObject.status != ObjectStatus::HEALTHY)
			return;

		// Mark game object for deletion
		gameObjectsToDelete.push_back(&gameObject);
		gameObject.status = ObjectStatus::MARKED_FOR_DESTROY;

		// Notify components that game object is marked for deletion
		for (Component* component : gameObject.components)
			componentManager.destroy(*component);
	}
	void GameObjectManager::destroyImmediately(GameObject& gameObject) {
		// Destroy each component attached to this game object immediately
		while (gameObject.components.size() > 0)
			componentManager.destroyImmediately(*gameObject.components.front());

		// If this game object is currently marked for deletion, remove it from the list
		if (gameObject.status == ObjectStatus::MARKED_FOR_DESTROY)
			gameObjectsToDelete.remove(&gameObject);

		// Erase game object
		gameObjects.erase(gameObject.node);
	}
	void GameObjectManager::destroyGameObjects() {
		for (GameObject& gameObject : gameObjects)
			destroy(gameObject);
	}
	void GameObjectManager::destroyGameObjectsImmediately() {
		while (gameObjects.size() > 0) {
			GameObject& gameObject = gameObjects.front();
			destroyImmediately(gameObject);
		}
	}
	void GameObjectManager::collectGarbage() {
		// Note: A while loop is used because deleting a game object can cause other game objects to be deleted
		// Do not replace with any other type of loop
		// Do not replace std::list for s_gameObjectsToDeleteList with any other data structures. New game objects to be deleted must be added to the back, not the front
		componentManager.collectGarbage();
		while (gameObjectsToDelete.size() > 0) {
			GameObject* gameObject = gameObjectsToDelete.front();
			gameObjects.erase(gameObject->node);
			gameObjectsToDelete.pop_front();
		}
	}

}
