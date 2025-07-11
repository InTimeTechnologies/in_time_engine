#pragma once

// Dependencies | std
#include <list>

// Dependencies | glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

// Dependencies | OpenGLEngine
#include "GLCamera.h"

namespace gl {
	class Camera2D : public Camera {
		// Friends
		friend class GLEngine;

		// Object
		public:
			// Properties
			float viewSize = 16.0f;

			// Constructors | Destructor
			Camera2D();
			~Camera2D();

			// Camera | Functions
			glm::mat4 getCameraMatrix() override;
	};
}
