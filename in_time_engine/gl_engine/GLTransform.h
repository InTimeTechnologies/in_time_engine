#pragma once

// Dependencies | std
#include <list>

// Dependencies | utility
#include <utility/IdFactory.h>

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

// Dependencies | OpenGLRenderer
#include "GLBuffer.h"

namespace gl {
	class Transform {
		// Friends
		friend class GLEngine;

		// Static
		private:
			// Properties
			static int s_initialTransformCapacity;
			static Buffer* s_transformBuffer;
			static util::IdFactory s_idFactory;

			// Functions
			static void s_init();
			static void s_deinit();

		// Object
		private:
			// Properties
			int transformIndex = -1;

		public:
			// Constructor / Destructor
			Transform();
			Transform(const glm::mat4& tranform);
			Transform(const Transform& glslTransform) = delete;
			Transform(const Transform&& glslTransform) = delete;
			~Transform();
			
			// Assignment operators
			Transform& operator=(const Transform& glslTransform) = delete;
			Transform& operator=(Transform&& glslTransform) = delete;

			// Getters
			int getIndex() const;

			// Functions
			void setTransform(const glm::mat4& transformMatrix);
	};
}
