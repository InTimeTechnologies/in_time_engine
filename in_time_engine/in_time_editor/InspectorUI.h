#pragma once

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | in_time_editor
#include "ComponentAdderPopupUI.h"

namespace it {
	// Forward declarations
	class GameObject;
	class Transform;
	class Component;

	class InspectorUI {
		// Friends
		friend class InTimeEditor;

		// Enum
		enum class Actions {
			CREATE_GAME_OBJECT,
			DELETE_GAME_OBJECT,
		};

		// Object
		private:
			// Properties
			GameObject* gameObject{ nullptr };
			glm::vec3 rotation{ 0.0f };
			bool isOpen{ true };
			bool isLocked{ false };
			ComponentAdderPopupUI componentAdderPopupUI{};

			// Functions
			void inspectGameObject();
			void inspectTransform();
			void inspectComponents();
			void inspectComponent(it::Component& component);
			void renderAddComponentButton();

		public:
			// Properties
			bool locked = false;

			// Operators
			InspectorUI& operator=(const InspectorUI& inspector) = default;
			InspectorUI& operator=(InspectorUI&& inspector) = default;

			// Setters
			void setGameObject(GameObject* gameObject);

			// Functions
			void update();
	};
}
