#pragma once

// Dependencies | in_time_engine
#include "../Component.h"
#include "../GameObject.h"
#include "../EngineEvents.h"
#include "../InTimeEngine.h"

// Dependencies | glm
#include <glm/glm.hpp>

namespace it {
	class Transformation : public Component, public UpdateEvent {
		// Object
		public:
			// Properties
			glm::vec3 translation = glm::vec3(0);
			glm::vec3 rotation = glm::vec3(0);
			glm::vec3 scale = glm::vec3(1);

			// Constructor / Destructor
			Transformation(GameObject& gameObject) : Component(gameObject, typeid(Transformation)) {

			}
			~Transformation() = default;

			// Functions
			void onPreUpdate() override {
				InTimeEngine* inTimeEngine = InTimeEngine::s_getSingleton();
				if (inTimeEngine == nullptr)
					return;

				float deltaTime = inTimeEngine->coreTime.getDeltaTimeF();

				Transform& transform = getGameObject().transform;
				if (translation != glm::vec3(0))
					transform.translateBy(translation * deltaTime);
				if (rotation != glm::vec3(0))
					transform.rotateBy(rotation * deltaTime);
				if (scale != glm::vec3(1))
					transform.scaleBy(scale * deltaTime);
			}
	};
}