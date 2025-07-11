#include "Camera2D.h"

// class GPUCamera2D

// Static | private

// Properties
std::list<it::Camera2D*> it::Camera2D::s_camera2DList = std::list<it::Camera2D*>();

// Functions
void it::Camera2D::s_updateTransforms() {
	for (Camera2D* camera2D : s_camera2DList) {
		it::GameObject& gameObject = camera2D->getGameObject();
		camera2D->camera2D.position = gameObject.transform.position;
	}
}

// Object | public

// Constructor / Destructor
it::Camera2D::Camera2D(GameObject& gameObject) : Component(gameObject, typeid(Camera2D)) {
	s_camera2DList.push_back(this);
	node = std::prev(s_camera2DList.end());
}
it::Camera2D::~Camera2D() {
	s_camera2DList.erase(node);
}
