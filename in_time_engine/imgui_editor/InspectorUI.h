#pragma once

// Dependencies | glm
#include <glm/glm.hpp>

namespace it {
	// Forward declarations
	class GameObject;
	class Transform;
	class Component;

	class InspectorUI {
		// Static
		private:
			// Properties
			static InspectorUI* singleton;

		public:
			// Getters
			static InspectorUI* getSingleton();

		// Object
		private:
			// Properties
			GameObject* gameObject = nullptr;
			
			glm::vec3 rotation = glm::vec3(0.0f);

			bool resize = false;

			// Functions
			void inspectTransform(it::Transform& transform);
			void inspectComponent(it::Component& component);

		public:
			// Properties
			bool locked = false;

			// Constructor / Destructor
			InspectorUI();
			InspectorUI(const InspectorUI& inspector) = default;
			InspectorUI(InspectorUI&& inspector) = default;
			~InspectorUI();

			// Operators
			InspectorUI& operator=(const InspectorUI& inspector) = default;
			InspectorUI& operator=(InspectorUI&& inspector) = default;

			// Setters
			void setGameObject(GameObject* gameObject);

			// Functions
			void update();
	};
}
