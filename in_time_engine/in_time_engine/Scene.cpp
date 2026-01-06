#include "Scene.h"

// Dependencies | std
#include <vector>
#include <unordered_map>

// Dependencies | in_time_engine
#include "GameObject.h"
#include "Component.h"
#include "json_serializer.h"
#include "CustomComponentSerializer.h"

namespace it {
	// class Scene

	// Functions
	void Scene::update() {
		std::vector<size_t> gameObjectsToRemove{};
		for (size_t i = 0; i < gameObjects.size(); i++) {
			std::shared_ptr<it::GameObject*> gameObjectSharedPtr = gameObjects[i].lock();
			if (!gameObjectSharedPtr)
				gameObjectsToRemove.push_back(i);
		}
		while (gameObjectsToRemove.size() > 0) {
			size_t indexToErase = gameObjectsToRemove.back();
			gameObjects.erase(gameObjects.begin() + indexToErase);
			gameObjectsToRemove.pop_back();
		}
	}
	void Scene::serialize(nlohmann::ordered_json& json) {
		// Update scene
		update();

		// SceneSerializer json to return
		json.clear();

		// Set scene name
		json["scene"] = name;

		// Serialize GameObjects
		json["gameObjects"] = nlohmann::ordered_json::array();
		for (size_t i = 0; i < gameObjects.size(); ++i) {
			if (const std::shared_ptr<GameObject*> sharedGameObjectPtr = gameObjects[i].lock()) {
				if (sharedGameObjectPtr) {
					GameObject* gameObject = *sharedGameObjectPtr;
					json["gameObjects"].push_back(*gameObject);
				}
			}
		}

		// Associate ids to GameObject pointers
		std::unordered_map<GameObject*, size_t> idToGameObjectMap{};
		for (size_t i = 0; i < gameObjects.size(); ++i) {
			if (const std::shared_ptr<GameObject*> sharedGameObjectPtr = gameObjects[i].lock()) {
				if (!sharedGameObjectPtr)
					continue;
				GameObject* gameObject = *sharedGameObjectPtr;
				idToGameObjectMap[gameObject] = i;
			}
		}

		// Serialize transform relationships
		nlohmann::ordered_json transformRelationshipsJson;
		for (const auto& [gameObject, id] : idToGameObjectMap) {
			if (gameObject->transform.getParent() == nullptr)
				continue;

			nlohmann::ordered_json transformRelationshipJson{
				{ "gameObject", id },
				{ "parent", idToGameObjectMap[gameObject->transform.getParent()->getGameObject()]}
			};

			json["transformRelationships"].push_back(transformRelationshipJson);
		}

		// To-Do: Associate ids to Component pointers
		std::unordered_map<Component*, size_t> idToComponentMap{};

		// To-Do: Serialize component relationships
		nlohmann::ordered_json componentsJson;
	}

	void Scene::deserialize(const nlohmann::ordered_json& json) {
		// Update scene
		update();

		// Get InTimeEngine's GameObjectManager
		it::InTimeEngine* inTimeEngine = it::InTimeEngine::s_getSingleton();
		if (inTimeEngine == nullptr)
			return;
		it::GameObjectManager& goManager = inTimeEngine->gameObjectManager;

		// Local variables
		std::vector<GameObject*> tempGameObjects{};

		// Deserialize game objects
		const nlohmann::ordered_json& gameObjectsJson = json.at("gameObjects");
		for (const nlohmann::ordered_json& gameObjectJson : gameObjectsJson) {
			std::cout << gameObjectJson.dump() << std::endl;
			it::GameObject& gameObject = goManager.createGameObject();
			gameObjectJson.get_to(gameObject);
			tempGameObjects.push_back(&gameObject);
		}

		// Associate ids to GameObject pointers
		std::unordered_map<GameObject*, size_t> idToGameObjectMap{};
		for (size_t i = 0; i < gameObjects.size(); ++i) {
			if (const std::shared_ptr<GameObject*> sharedGameObjectPtr = gameObjects[i].lock()) {
				if (!sharedGameObjectPtr)
					continue;
				GameObject* gameObject = *sharedGameObjectPtr;
				idToGameObjectMap[gameObject] = i;
			}
		}

		// Deserialize transform relationships
		for (const nlohmann::ordered_json& transformRelationshipJson : json.at("transformRelationships")) {
			int gameObjectIndex{ -1 };
			int parentGameObjectIndex{ -1 };

			transformRelationshipJson.at("gameObject").get_to(gameObjectIndex);
			transformRelationshipJson.at("parent").get_to(parentGameObjectIndex);

			GameObject* gameObject = tempGameObjects[gameObjectIndex];
			GameObject* parentGameObject = tempGameObjects[parentGameObjectIndex];
			
			gameObject->transform.setParent(&parentGameObject->transform);
		}

		// Get game objects' weak pointer
		gameObjects.reserve(tempGameObjects.size());
		for (GameObject* gameObject : tempGameObjects)
			gameObjects.push_back(gameObject->getWeakPointer());

		// To-Do: Associate ids to Component pointers

		// To-Do: Serialize component relationships

	}

	bool Scene::serialize(Component* component, nlohmann::ordered_json& json) {
		const std::type_info& typeInfo = component->getTypeInfo();

		if (typeInfo == typeid(EmptyComponent)) {
			json = nlohmann::ordered_json::object();

			return true;
		}
		else if (typeInfo == typeid(Transformation)) {
			Transformation* transformation = reinterpret_cast<Transformation*>(component);
			
			json = nlohmann::ordered_json::object();
			json["translation"] = transformation->translation;
			json["rotation"] = transformation->rotation;
			json["scale"] = transformation->scale;

			return true;
		}
		else if (typeInfo == typeid(PhysicsTransformation)) {
			PhysicsTransformation* physicsTransformation = reinterpret_cast<PhysicsTransformation*>(component);

			json = nlohmann::ordered_json::object();
			json["translation"] = physicsTransformation->translation;
			json["rotation"] = physicsTransformation->rotation;
			json["scale"] = physicsTransformation->scale;

			return true;
		}
		else
			return false;
	}
}
