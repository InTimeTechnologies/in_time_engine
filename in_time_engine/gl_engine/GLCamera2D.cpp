#include "GLCamera2D.h"

// Dependencies | CoreEngine
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// class Camera2D

// Object | private

// Constructors / Destructor
gl::Camera2D::Camera2D() {
	farClippingPlane = -1.0f;
	nearClippingPlane = 1000.0f;
}
gl::Camera2D::~Camera2D() {

}

// Functions
glm::mat4 gl::Camera2D::getCameraMatrix() {
	if (renderTarget == nullptr)
		return glm::mat4(1);

	int width = 0;
	int height = 0;
	glfwGetFramebufferSize(renderTarget, &width, &height);

	if (width <=0 || height <= 0)
		return glm::mat4(1);

	if (renderFullScreen) {
		float aspectRatio = (float)width / (float)height;
		float left = -viewSize * 0.5f;
		float right = viewSize * 0.5f;
		float down = -viewSize * 0.5f / aspectRatio;
		float up = viewSize * 0.5f / aspectRatio;
	
		glm::mat4 viewMatrix = glm::ortho(left, right, down, up, nearClippingPlane, farClippingPlane);

		glm::mat4 cameraTransform = glm::mat4(1);
		glm::vec3 cameraTranslation = position;
		cameraTranslation.x *= -1.0f;
		cameraTranslation.y *= -1.0f;
		cameraTransform = glm::translate(cameraTransform, cameraTranslation);
		cameraTransform *= glm::mat4_cast(orientation);

		return cameraTransform * viewMatrix;	
	}
	else {
		float aspectRatio = (float)width / (float)height;
		float left = -viewSize * 0.5f;
		float right = viewSize * 0.5f;
		float down = -viewSize * 0.5f / aspectRatio;
		float up = viewSize * 0.5f / aspectRatio;

		glm::mat4 viewMatrix = glm::ortho(left, right, down, up, nearClippingPlane, farClippingPlane);
		// glm::mat4 viewMatrix = glm::ortho(left, right, down, up, 1.0f, -1.0f);

		glm::mat4 cameraTransform = glm::mat4(1);
		glm::vec3 cameraTranslation = position;
		cameraTranslation.x *= -1.0f;
		cameraTranslation.y *= -1.0f;
		cameraTransform = glm::translate(cameraTransform, cameraTranslation);
		cameraTransform *= glm::mat4_cast(orientation);
		
		return cameraTransform * viewMatrix;
	}
}

// Proper order of transformations:
// 1. Scale
// 2. Rotate
// 3. Translate
