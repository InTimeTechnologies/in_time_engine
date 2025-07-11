#if defined(OPENGL_ENGINE) && defined(GLFW_ENGINE)
#pragma once

// Dependencies | in_time_engine
#include "../Component.h"
#include "../GameObject.h"
#include "../EngineEvents.h"
#include "../gpu_component/Camera2D.h"

// Dependencies | gl_engine
#include <gl_engine/GLCamera2D.h>

// Dependencies | in_time_engine
#include <glfw_engine/WindowWrapper.h>

namespace it {
	class CameraControl2D : public UpdateEvent {
		// Object
		public:
			// Properties
			Camera2D* camera2D = nullptr;
			float translationStrength = 1.0f;
			float zoomStrength = 2.5f;

			// Constructor / Destructor
			CameraControl2D() = default;
			~CameraControl2D() = default;

			// Functions
			void onPreUpdate() override {
				if (camera2D == nullptr)
					return;
				
				glfw::WindowWrapper* windowWrapper = (glfw::WindowWrapper*)glfwGetWindowUserPointer(camera2D->camera2D.renderTarget);
				if (windowWrapper == nullptr)
					return;

				it::GameObject& cameraGO = camera2D->getGameObject();
				float deltaTime = InTimeEngine::s_getSingleton()->coreTime.getDeltaTimeF();

				glfw::Input& input = windowWrapper->input;
				glfw::Key right = input.getKey(glfw::KeyCode::RIGHT_ARROW);
				glfw::Key left = input.getKey(glfw::KeyCode::LEFT_ARROW);
				glfw::Key up = input.getKey(glfw::KeyCode::UP_ARROW);
				glfw::Key down = input.getKey(glfw::KeyCode::DOWN_ARROW);
				glfw::Key reset = input.getKey(glfw::KeyCode::ALPHA_0);
				glfw::Key zoomIn = input.getKey(glfw::KeyCode::EQUAL);
				glfw::Key zoomOut = input.getKey(glfw::KeyCode::MINUS);
				glfw::Key resetViewSize = input.getKey(glfw::KeyCode::PERIOD);
				
				// Update camera position
				glm::vec3 position = cameraGO.transform.position;
				position.x += (right.pressed - left.pressed) * deltaTime * translationStrength;
				position.y += (up.pressed - down.pressed) * deltaTime * translationStrength;
				position = reset.pressed ? glm::vec3(0.0f) : position;
				cameraGO.transform.setPosition(position);

				// Update view size
				float viewSize = camera2D->camera2D.viewSize;
				viewSize += (zoomOut.pressed - zoomIn.pressed) * deltaTime * zoomStrength;
				viewSize = resetViewSize.pressed ? 16.0f : viewSize;
				
				camera2D->camera2D.viewSize = viewSize;
			}
	};
}

#endif
