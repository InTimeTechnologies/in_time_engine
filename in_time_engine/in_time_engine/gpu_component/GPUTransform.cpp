#include "GPUTransform.h"

namespace it {
	// class GPUTransform

	// Object | private

	// Properties
	std::list<GPUTransform*> GPUTransform::s_gpuTransformList{};

	// Functions
	void GPUTransform::s_synch() {
		for (GPUTransform* gpuTransform : s_gpuTransformList)
			gpuTransform->synch();
	}

	// Object | public

	// Constructor / Destructor
	GPUTransform::GPUTransform() {
		s_gpuTransformList.push_back(this);
		node = std::prev(s_gpuTransformList.end());
	}
	GPUTransform::~GPUTransform() {
		s_gpuTransformList.erase(node);
	}

	// Getters
	const std::type_info& GPUTransform::getTypeInfo() const {
		return typeid(GPUTransform);
	}

	// Functions
	void GPUTransform::synch() {
		Transform& transform = gameObject->transform;
		if (!transform.isDirty())
			return;
		glm::mat4 globalMatrix = transform.getGlobalMatrix();
		glTransform.setTransform(globalMatrix);
	}

	// Events
	void GPUTransform::onAddToGameObject() {
		gameObject->transform.makeDirty();
	}
}
