#pragma once

// Depenencies | std
#include <string>
#include <vector>
#include <filesystem>
#include <memory>

// Depenencies | utility
#include <utility/BinaryRangeTree.h>

// Dependencies | nlohmann
#include <nlohmann/json.hpp>

namespace it {
	// Forward declarations
	class GameObject;
	class Component;
	struct CustomComponentSerializer;
	struct CustomComponentDeserializer;

	class Scene {
		public:
			// Object

			// Properties
			std::string name{ "scene" };
			std::vector<std::weak_ptr<GameObject*>> gameObjects{};

			CustomComponentSerializer* customComponentSerializer{ nullptr };
			CustomComponentDeserializer* customComponentDeserializer{ nullptr };

			// Functions
			void update();
			void serialize(nlohmann::ordered_json& json);
			void deserialize(const nlohmann::ordered_json& json);

			bool serialize(Component* component, nlohmann::ordered_json& json);
	};
}
