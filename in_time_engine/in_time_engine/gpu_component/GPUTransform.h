#pragma once

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | in_time_engine
#include "../GameObject.h"
#include "../Component.h"

// Dependencies | gl_engine
#include <gl_engine/GLTransform.h>

namespace it {
	class GPUTransform : public Component {
		// Object
		public:
			// Properties
			gl::Transform glTransform = gl::Transform();

			// Constructor / Destructor
			GPUTransform(GameObject& gameObject) : Component(gameObject, typeid(GPUTransform)) {
				Transform& transform = gameObject.transform;
				assert(transform.gpuTransform == nullptr);
				transform.gpuTransform = this;
				transform.hintGPUUpdate();
			}
			GPUTransform(const GPUTransform& gpuTransform) = delete;
			GPUTransform(GPUTransform&& gpuTransform) = delete;
			~GPUTransform() = default;

			// Assignment operators
			GPUTransform& operator=(const GPUTransform& gpuTransform) = delete;
			GPUTransform& operator=(GPUTransform&& gpuTransform) = delete;

			// Functions
			void update() {
				Transform* transform = &getGameObject().transform;
				glm::mat4 globalMatrix = transform->getGlobalMatrix();
				glTransform.setTransform(globalMatrix);
			}
			void update(const glm::mat4& globalMatrix) {
				glTransform.setTransform(globalMatrix);
			}

			// Functions | Component
			void onDestroy() override {
				Transform& transform = getGameObject().transform;
				assert(transform.gpuTransform != nullptr);
				transform.unhintGPUUpdate();
				transform.gpuTransform = nullptr;
			}
	};
}
