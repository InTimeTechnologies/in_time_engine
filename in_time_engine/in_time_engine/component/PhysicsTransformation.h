#pragma once

// Dependencies | std
#include <iostream>

// Dependencies | in_time_engine
#include "../Component.h"
#include "../GameObject.h"
#include "../EngineEvents.h"
#include "../InTimeEngine.h"

// Dependencies | glm
#include <glm/glm.hpp>

namespace it {
	class PhysicsTransformation : public Component, public PhysicsUpdateEvent2D {
		// Object
		public:
			// Properties
			glm::vec3 translation = glm::vec3(0);
			glm::vec3 rotation = glm::vec3(0);
			glm::vec3 scale = glm::vec3(1);

			// Constructor / Destructor
			PhysicsTransformation(GameObject& gameObject) : Component(gameObject, typeid(PhysicsTransformation)) {

			}
			~PhysicsTransformation() = default;

			// Functions
			void onPrePhysicsUpdate2D() override {
				InTimeEngine* inTimeEngine = InTimeEngine::s_getSingleton();
				if (inTimeEngine == nullptr)
					return;

				float fixedScaledDeltaTime = inTimeEngine->physicsTime.getScaledDeltaTimeF();

				Transform& transform = getGameObject().transform;
				if (translation != glm::vec3(0))
					transform.translateBy(translation * fixedScaledDeltaTime);
				if (rotation != glm::vec3(0))
					transform.rotateBy(rotation * fixedScaledDeltaTime);
				if (scale != glm::vec3(1))
					transform.scaleBy(scale * fixedScaledDeltaTime);
			}
		};
}