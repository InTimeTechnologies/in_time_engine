#include "GLTransform.h"

// Dependencies | std
#include <limits>

// Dependencies | std
#include <cassert>

// class OpenGLTransform

// Static | Private

// Properties
int gl::Transform::s_initialTransformCapacity = 60000;
int gl::Transform::s_transformCapacity = gl::Transform::s_initialTransformCapacity;
gl::Buffer* gl::Transform::s_transformBuffer = nullptr;
BinaryRangeTree<int> gl::Transform::s_idTracker{ Range<int>{ 0, std::numeric_limits<int>::max() } };

// Functions
void gl::Transform::s_init() {
	s_deinit();
	s_transformBuffer = new Buffer(sizeof(glm::mat4) * s_initialTransformCapacity, nullptr, Buffer::Type::SHADER_STORAGE_BUFFER);
}
void gl::Transform::s_deinit() {
	if (s_transformBuffer == nullptr) {
		delete s_transformBuffer;
		s_transformBuffer = nullptr;
	}
}

// Object | public

// Constructor / Destructor
gl::Transform::Transform() {
	bool success = s_idTracker.popLeast(&transformIndex);
	assert(success);
	if (transformIndex > s_transformCapacity) {
		gl::Buffer* newTransformBuffer = new gl::Buffer(sizeof(glm::mat4) * s_initialTransformCapacity, nullptr, Buffer::Type::SHADER_STORAGE_BUFFER);
		newTransformBuffer->subCopy(*s_transformBuffer, 0LL, 0LL, s_transformBuffer->getMemorySize());
		delete s_transformBuffer;
		s_transformBuffer = newTransformBuffer;
	}
}
gl::Transform::Transform(const glm::mat4& matrix) : Transform() {
	s_transformBuffer->subwrite(sizeof(glm::mat4) * transformIndex, sizeof(glm::mat4), &matrix);
}
gl::Transform::~Transform() {
	s_idTracker.push(transformIndex);
}

// Object | public

// Functions
int gl::Transform::getIndex() const {
	return transformIndex;
}

// Functions
void gl::Transform::setTransform(const glm::mat4& transformMatrix) {
	s_transformBuffer->subwrite(transformIndex * sizeof(glm::mat4), sizeof(glm::mat4), &transformMatrix);
}
