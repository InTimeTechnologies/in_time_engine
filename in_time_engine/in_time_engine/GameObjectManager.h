#pragma once

// Dependencies | in_time_engine
#include "GameObject.h"
#include "Component.h"
#include "ComponentManager.h"

namespace it {
	class GameObjectManager {
		// Friends
		friend class InTimeEngine;

		private:
			// Properties
			std::list<GameObject> gameObjectsToDeleteList{};

		public:
			// Properties
			int defaultId{ 0 };
			std::string defaultName{ "game object" };
			std::list<GameObject> gameObjects{};
			std::list<GameObject*> gameObjectsToDelete{};
			ComponentManager componentManager{};

			// Constructor / Destructor
			GameObjectManager() = default;
			GameObjectManager(const GameObjectManager& other) = delete;
			~GameObjectManager();

			// Operators | assignment
			GameObjectManager& operator=(const GameObjectManager& other) = delete;
			GameObjectManager& operator=(GameObjectManager&& other) = delete;

			// Functions
			GameObject& createGameObject();
			GameObject& createGameObject(int id);
			GameObject& createGameObject(const std::string& name);
			GameObject& createGameObject(int id, const std::string& name);
			void destroy(GameObject& gameObject);
			void destroyImmediately(GameObject& gameObject);
			void destroyGameObjects();
			void destroyGameObjectsImmediately();
			void collectGarbage();
	};
}
