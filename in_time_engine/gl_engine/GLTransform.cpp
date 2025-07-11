#include "GLTransform.h"

// class OpenGLTransform

// Static | Private

// Properties
int gl::Transform::s_initialTransformCapacity = 60000;
gl::Buffer* gl::Transform::s_transformBuffer = nullptr;
util::IdFactory gl::Transform::s_idFactory = util::IdFactory(s_initialTransformCapacity);

// Functions
void gl::Transform::s_init() {
	s_deinit();
	s_transformBuffer = new Buffer(Buffer(BufferType::SHADER_STORAGE_BUFFER, BufferUsage::STREAM_DRAW, sizeof(glm::mat4) * s_initialTransformCapacity, nullptr));
}
void gl::Transform::s_deinit() {
	if (s_transformBuffer == nullptr) {
		delete(s_transformBuffer);
		s_transformBuffer = nullptr;
	}
	s_idFactory = util::IdFactory(s_initialTransformCapacity);
}

// Object | public

// Constructor / Destructor
gl::Transform::Transform() {
	transformIndex = s_idFactory.pop();
}
gl::Transform::Transform(const glm::mat4& matrix) : Transform() {
	s_transformBuffer->subwrite(sizeof(glm::mat4) * transformIndex, sizeof(glm::mat4), &matrix);
}
gl::Transform::~Transform() {
	s_idFactory.push(transformIndex);
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
