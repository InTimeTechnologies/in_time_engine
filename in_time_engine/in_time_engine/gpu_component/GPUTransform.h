#pragma once

// Dependencies | std
#include <list>

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | in_time_engine
#include "../GameObject.h"
#include "../Component.h"

// Dependencies | gl_engine
#include <gl_engine/GLTransform.h>

namespace it {
	class GPUTransform : public Component {
		// Friends
		friend class InTimeEngine;

		// Static
		private:
			// Properties
			static std::list<GPUTransform*> s_gpuTransformList;

			// Functions
			static void s_synch();

		// Object
		private:
			// Properties
			std::list<GPUTransform*>::iterator node{};

		public:
			// Properties
			gl::Transform glTransform = gl::Transform();

			// Constructor / Destructor
			GPUTransform();
			GPUTransform(const GPUTransform& gpuTransform) = delete;
			GPUTransform(GPUTransform&& gpuTransform) = delete;
			~GPUTransform();

			// Assignment operators
			GPUTransform& operator=(const GPUTransform& gpuTransform) = delete;
			GPUTransform& operator=(GPUTransform&& gpuTransform) = delete;

			// Getters
			const std::type_info& getTypeInfo() const override;

			// Functions
			void synch();

			// Events
			void onAddToGameObject() override;
	};
}
