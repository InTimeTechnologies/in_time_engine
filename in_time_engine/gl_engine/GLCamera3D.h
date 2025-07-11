#pragma once

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | OpenGLEngine
#include "GLCamera.h"

namespace gl {
	class Camera3D : public Camera {
		// Object
		public:
			// Properties
			glm::vec3 upVector = glm::vec3(0, 1, 0);
			float angleInDegrees = 110.0f;

			// Constructor / Destructor
			Camera3D();
			~Camera3D();

			// Camera | Functions
			glm::mat4 getCameraMatrix() override;
	};
}