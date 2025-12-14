#include "GLCamera3D.h"

// Dependencies | glm
#include <glm/gtx/quaternion.hpp>

// class Camera3D

// Object | public

// Constructor / Destructor
gl::Camera3D::Camera3D() {

}
gl::Camera3D::~Camera3D() {

}

// Camera | Functions
glm::mat4 gl::Camera3D::getCameraMatrix() {
	if (renderTarget == nullptr)
		return glm::mat4(1);

	int width = 0;
	int height = 0;
	glfwGetFramebufferSize(renderTarget, &width, &height);

	if (width <=0 || height <= 0)
		return glm::mat4(1);

	if (renderTarget == nullptr || width == 0 || height == 0)
		return glm::mat4(1);
	
	glm::vec3 lookAtDirection = glm::rotate(orientation, glm::vec3(0, 0, -1));
	glm::mat4 view = glm::lookAt(position, lookAtDirection + position, upVector);
	float aspectRatio = (float)width / (float)height;
	glm::mat4 projection = glm::perspective(glm::radians(angleInDegrees), aspectRatio, nearClippingPlane, farClippingPlane);


	glm::mat4 cameraTransform = glm::mat4(1);
	cameraTransform *= glm::mat4_cast(orientation);

	return projection * view;
}
