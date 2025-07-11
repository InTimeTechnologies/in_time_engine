#include "GLCamera.h"

// class Camera

// Static | public

// Properties
std::list<gl::Camera*> gl::Camera::cameraList = std::list<gl::Camera*>();
gl::Camera* gl::Camera::mainCamera = nullptr;
gl::Camera* gl::Camera::debugCamera = nullptr;

// Object | public

// Constructor / Destructor
gl::Camera::Camera() {
	cameraList.push_back(this);
	cameraNode = std::prev(cameraList.end());
}
gl::Camera::~Camera() {
	cameraList.erase(cameraNode);
}
