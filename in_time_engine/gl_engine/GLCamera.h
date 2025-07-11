#pragma once

// Dependencies | std
#include <list>

// Dependencies | glm
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

namespace gl {
	struct ViewportRect {
		int x = 0;
		int y = 0;
		int width = 0;
		int height = 0;
	};

	class Camera {
		// Friends
		friend class GLEngine;

		// Static
		public:
			// Properties
			static std::list<Camera*> cameraList;
			static Camera* mainCamera;
			static Camera* debugCamera;

		// Object
		private:
			// Properties
			std::list<Camera*>::iterator cameraNode;

		public:
			// Properties
			glm::vec4 backgroundColor = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
			float clearDepth = -1.0f;
			glm::vec3 position = glm::vec3(0.0f, 0.0f, -0.5f);
			glm::quat orientation = glm::quat(1, 0, 0, 0);
			bool renderFullScreen = true;
			float nearClippingPlane = 0.1f;
			float farClippingPlane = 1000.0f;
			ViewportRect viewportRect;
			GLFWwindow* renderTarget = nullptr;

		public:
			// Constructor / Destructor
			Camera();
			virtual ~Camera();

			// Pure virtual functions
			virtual glm::mat4 getCameraMatrix() = 0;
	};
}
