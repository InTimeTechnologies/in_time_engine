#include "GLBuffer.h"

// class Buffer

// Static | private

// Properties
gl::BufferType gl::Buffer::defaultBufferType = gl::BufferType::VERTEX_BUFFER;
gl::BufferUsage gl::Buffer::defaultBufferUsage = gl::BufferUsage::STREAM_DRAW;

// Functions | Helpers
bool gl::Buffer::validateBufferType(gl::BufferType bufferType) {
	switch (bufferType) {
		case gl::BufferType::VERTEX_BUFFER:
		case gl::BufferType::ATOMIC_COUNTER_BUFFER:
		case gl::BufferType::COPY_READ_BUFFER:
		case gl::BufferType::COPY_WRITE_BUFFER:
		case gl::BufferType::DISPATCH_INDIRECT_BUFFER:
		case gl::BufferType::DRAW_INDIRECT_BUFFER:
		case gl::BufferType::INDEX_BUFFER:
		case gl::BufferType::PIXEL_PACK_BUFFER:
		case gl::BufferType::PIXEL_UNPACK_BUFFER:
		case gl::BufferType::QUERY_BUFFER:
		case gl::BufferType::SHADER_STORAGE_BUFFER:
		case gl::BufferType::TEXTURE_BUFFER:
		case gl::BufferType::TRANSFORM_FEEDBACK_BUFFER:
		case gl::BufferType::UNIFORM_BUFFER:
			return true;
		default:
			return false;
	}
}
bool gl::Buffer::validateBufferUsage(gl::BufferUsage bufferUsage) {
	switch (bufferUsage) {
		case gl::BufferUsage::STREAM_DRAW:
		case gl::BufferUsage::STREAM_READ:
		case gl::BufferUsage::STREAM_COPY:
		case gl::BufferUsage::STATIC_DRAW:
		case gl::BufferUsage::STATIC_READ:
		case gl::BufferUsage::STATIC_COPY:
		case gl::BufferUsage::DYNAMIC_DRAW:
		case gl::BufferUsage::DYNAMIC_READ:
		case gl::BufferUsage::DYNAMIC_COPY:
			return true;
		default:
			return false;
	}
}

// Static | public

// Getters
gl::BufferType gl::Buffer::getDefaultBufferType() {
	return defaultBufferType;
}
gl::BufferUsage gl::Buffer::getDefautBufferUsage() {
	return defaultBufferUsage;
}

// Setters
void gl::Buffer::setDefaultBufferType(gl::BufferType bufferType) {
	if (validateBufferType(bufferType))
		defaultBufferType = bufferType;
}
void gl::Buffer::setDefaultBufferUsage(gl::BufferUsage bufferUsage) {
	if (validateBufferUsage(bufferUsage))
		defaultBufferUsage = bufferUsage;
}

// Functions
void gl::Buffer::unbind(gl::BufferType type) {
	glBindBuffer((unsigned int)type, 0);
}
void gl::Buffer::unbindAll() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
	glBindBuffer(GL_COPY_READ_BUFFER, 0);
	glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
	glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, 0);
	glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	glBindBuffer(GL_QUERY_BUFFER, 0);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_BUFFER, 0);
	glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
bool gl::Buffer::isBuffer(unsigned int id) {
	return glIsBuffer(id);
}

// Object | public

// Constructors / destructor
gl::Buffer::Buffer() {
	glCreateBuffers(1, &id);
	glNamedBufferData(id, memorySize, nullptr, (int)usage);
}
gl::Buffer::Buffer(gl::BufferType type, gl::BufferUsage usage, long long memorySize, void* data) : memorySize(memorySize), intendedUse(type), usage(usage) {
	glCreateBuffers(1, &id);
	glNamedBufferData(id, memorySize, data, (int)usage);
}
gl::Buffer::Buffer(gl::BufferType type, gl::BufferUsage usage, long long memorySize) : gl::Buffer(type, usage, memorySize, nullptr) {}
gl::Buffer::~Buffer() {
	glDeleteBuffers(1, &id);
}

// Getters
unsigned int gl::Buffer::getID() const {
	return id;
}
long long gl::Buffer::size() const {
	return memorySize;
}
gl::BufferType gl::Buffer::getBufferType() const {
	return intendedUse;
}
gl::BufferUsage gl::Buffer::getBufferUsage() const {
	return usage;
}

// Functions
bool gl::Buffer::bind() const {
	// Bind buffer
	glBindBuffer((unsigned int)intendedUse, id);

	// Return success
	return true;
}
void gl::Buffer::bind(gl::BufferType type) const {
	glBindBuffer((unsigned int)type, id);
}
void gl::Buffer::bindBufferBase(int bindingPoint) const {
	// Error check
	if (bindingPoint < 0)
		return;

	// Validate buffer type
	switch (intendedUse) {
		case gl::BufferType::ATOMIC_COUNTER_BUFFER:
		case gl::BufferType::TRANSFORM_FEEDBACK_BUFFER:
		case gl::BufferType::UNIFORM_BUFFER:
		case gl::BufferType::SHADER_STORAGE_BUFFER:
			break;
		default:
			return;
	}

	// Bind to binding point
	glBindBufferBase((unsigned int)intendedUse, bindingPoint, id);
}
void gl::Buffer::bindBufferBase(gl::BufferType glslBufferType, int bindingPoint) const {
	// Error check
	if (bindingPoint < 0)
		return;

	// Validate buffer type
	switch (glslBufferType) {
		case gl::BufferType::ATOMIC_COUNTER_BUFFER:
		case gl::BufferType::TRANSFORM_FEEDBACK_BUFFER:
		case gl::BufferType::UNIFORM_BUFFER:
		case gl::BufferType::SHADER_STORAGE_BUFFER:
			break;
		default:
			return;
	}

	// Bind to binding point
	glBindBufferBase((int)glslBufferType, bindingPoint, id);
}
void gl::Buffer::bindVertexBuffer(unsigned int bindingIndex, int offset, int stride) const {
	glBindVertexBuffer(bindingIndex, id, offset, stride);
}
void gl::Buffer::unbindVertexBuffer(unsigned int bindingIndex) const {
	glBindVertexBuffer(bindingIndex, id, 0, 0);
}
bool gl::Buffer::write(long long memorySize, const void* data, gl::BufferUsage usage) {
	if (!validateBufferUsage(usage))
		return false;
	this->usage = usage;

	glNamedBufferData(id, memorySize, data, (unsigned int)usage);
	return true;
}
bool gl::Buffer::subwrite(long long offset, long long size, const void* data) {
	if (offset + size > memorySize)
		return false;
	glNamedBufferSubData(id, offset, size, data);
	return true;
}
void gl::Buffer::getData(void* data) const {
	glGetNamedBufferSubData(id, 0, memorySize, data);
}
void gl::Buffer::getData(long long offset, long long size, void* data) const {
	glGetNamedBufferSubData(id, offset, size, data);
}
bool gl::Buffer::copy(gl::Buffer* buffer) {
	if (memorySize < buffer->memorySize)
		return false;
	
	glCopyNamedBufferSubData(buffer->id, id, 0, 0, buffer->memorySize);
	return true;
}
bool gl::Buffer::subCopy(gl::Buffer* buffer, long long readOffset, long long writeOffset, int size) {
	if (readOffset + size > buffer->memorySize || writeOffset + size > memorySize)
		return false;
	glCopyNamedBufferSubData(buffer->id, id, readOffset, writeOffset, buffer->memorySize);
	return true;
}
bool gl::Buffer::isBuffer() {
	return glIsBuffer(id);
}
