#include "GLBuffer.h"

// Dependencies | std
#include <cassert>

namespace gl {
	// class Buffer

	// Static | public

	// Functions
	void Buffer::s_unbind(Type type) {
		glBindBuffer(static_cast<unsigned int>(type), 0);
	}
	void Buffer::s_unbindAll() {
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
	void Buffer::s_unbindVertexBuffer(unsigned int bindingIndex) {
		glBindVertexBuffer(bindingIndex, 0U, 0LL, 0);
	}
	bool Buffer::s_isBuffer(unsigned int id) {
		return glIsBuffer(id);
	}

	// Object | public

	// Constructors / destructor
	Buffer::Buffer(long long memorySize) {
		// Allocate memory in GPU
		allocate(memorySize, nullptr);
	}
	Buffer::Buffer(long long memorySize, void* data) {
		// Allocate memory in GPU and upload data
		allocate(memorySize, data);
	}
	Buffer::Buffer(long long memorySize, void* data, Type type) {
		// Allocate memory in GPU and upload data
		allocate(memorySize, data);

		// Update properties
		this->type = type;
	}
	Buffer::Buffer(const Buffer& other) {
		copy(other);
	}
	Buffer::Buffer(Buffer&& other) noexcept {
		// Steal resources
		this->id = other.id;
		this->memorySize = other.memorySize;
		this->type = other.type;

		// Reset other
		other.id = 0U;
		other.memorySize = 0LL;
		other.type = Type::UNKNOWN;
	}
	Buffer::~Buffer() {
		free();
	}

	// Operator | assignment
	Buffer& Buffer::operator=(const Buffer& other) {
		copy(other);
		return *this;
	}
	Buffer& Buffer::operator=(Buffer&& other) noexcept {
		if (this == &other)
			return *this;

		// Deallocate current resources
		free();

		// Steal resources
		this->id = other.id;
		this->memorySize = other.memorySize;
		this->type = other.type;

		// Reset other
		other.id = 0U;
		other.memorySize = 0LL;
		other.type = Type::UNKNOWN;
		return *this;
	}

	// Getters
	unsigned int Buffer::getID() const {
		return id;
	}
	long long Buffer::getMemorySize() const {
		return memorySize;
	}
	Buffer::Type Buffer::getType() const {
		return type;
	}

	// Setters
	void Buffer::setType(Type type) {
		this->type = type;
	}

	// Functions
	void Buffer::swap(Buffer&& other) noexcept {
		std::swap(id, other.id);
		std::swap(memorySize, other.memorySize);
		std::swap(type, other.type);
		std::swap(dataStoreUsage, other.dataStoreUsage);
	}
	void Buffer::allocate(long long memorySize, const void* data, DataStoreUsage dataStoreUsage) {
		// Free any pior allocated data
		free();

		// Error check with verbose asserts
		assert(memorySize > 0LL && "Buffer memory size must be greater than zero");
		assert(dataStoreUsage != DataStoreUsage::UNKNOWN && "Data store usage must be valid and cannot be UNKNOWN");

		// Allocate buffer
		glCreateBuffers(1, &id);
		glNamedBufferStorage(id, memorySize, data, static_cast<GLbitfield>(dataStoreUsage));

		// Error check with verbose asserts
		assert(id != 0U && "Failed to allocate buffer; id was == 0 after allocation");

		// Update properties
		this->memorySize = memorySize;
		this->dataStoreUsage = dataStoreUsage;
	}
	void Buffer::free() {
		// Error check with verbose asserts
		if (id == 0U)
			return;

		// Delete buffer
		glDeleteBuffers(1, &id);

		// Update properties
		id = 0U;
		memorySize = 0LL;
		dataStoreUsage = DataStoreUsage::UNKNOWN;
	}
	void Buffer::bind() const {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(type != Type::UNKNOWN && "Buffer type must be set and cannot be UNKNOWN");

		glBindBuffer(static_cast<unsigned int>(type), id);
	}
	void Buffer::bind(Type type) const {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(type != Type::UNKNOWN && "Buffer type must be set and cannot be UNKNOWN");

		glBindBuffer(static_cast<unsigned int>(type), id);
	}
	void Buffer::bindBufferBase(unsigned int bindingPoint) const {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(type != Type::UNKNOWN && "Buffer type must be set and cannot be UNKNOWN");

		// Bind to binding point
		glBindBufferBase(static_cast<unsigned int>(type), bindingPoint, id);
	}
	void Buffer::bindBufferBase(Type type, unsigned int bindingPoint) const {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(type != Type::UNKNOWN && "Buffer type must be set and cannot be UNKNOWN");

		// Bind to binding point
		glBindBufferBase(static_cast<GLenum>(type), bindingPoint, id);
	}
	void Buffer::bindVertexBuffer(unsigned int bindingIndex, long long offset, int stride) const {
		// Error check with verbose asserts
		assert(stride > 0 && "Stride must be greater than 0");
		assert(offset >= 0LL && "Offsert cannot be negative (offset < 0)");

		// Bind to vertex binding index
		glBindVertexBuffer(bindingIndex, id, offset, stride);
	}
	void Buffer::getData(void* data) const {
		glGetNamedBufferSubData(id, 0LL, memorySize, data);
	}
	void Buffer::getData(long long offset, long long size, void* data) const {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(offset >= 0LL && "Offset cannot be negative");
		assert(size >= 0LL && "Size cannot be negative");
		assert(offset + size <= memorySize && "Requested range exceeds buffer size");

		// Copy data from GPU to CPU
		glGetNamedBufferSubData(id, offset, size, data);
	}
	void Buffer::subwrite(long long offset, long long size, const void* data) {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(offset >= 0LL && "Offset cannot be negative");
		assert(size >= 0LL && "Size cannot be negative");
		assert(offset + size <= memorySize && "Write range exceeds buffer size");

		glNamedBufferSubData(id, offset, size, data);
	}
	void Buffer::copy(const Buffer& other) {
		// If empty buffer
		if (other.id == 0U) {
			// Copy empty
			free();
			this->type = other.type;
			return;
		}

		// Allocate memory in GPU
		if (id == 0U || memorySize != other.memorySize || dataStoreUsage != other.dataStoreUsage)
			allocate(other.memorySize, nullptr, other.dataStoreUsage);

		// Error check with verbose asserts
		assert(id != 0U && "Failed to allocate buffer; id was == 0 after allocation");

		// Copy data
		glCopyNamedBufferSubData(other.id, id, 0, 0, other.memorySize);

		// Copy properties
		this->type = other.type;
	}
	void Buffer::subCopy(const Buffer& other, long long readOffset, long long writeOffset, long long size) {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(other.id != 0U && "Other buffer must be valid (other.id != 0)");
		assert(readOffset >= 0LL && "Read offset cannot be negative");
		assert(writeOffset >= 0LL && "Write offset cannot be negative");
		assert(readOffset + size <= other.memorySize && "Read range exceeds source buffer size");
		assert(writeOffset + size <= memorySize && "Write range exceeds destination buffer size");

		// Sub-copy
		glCopyNamedBufferSubData(other.id, id, readOffset, writeOffset, size);
	}
	void Buffer::clear(Format internalFormat, Format format, DataType dataType, const void* data) {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(internalFormat != Format::UNKNOWN && "Internal format must be valid (not UNKNOWN)");
		assert(format != Format::UNKNOWN && "Format must be valid (not UNKNOWN)");
		assert(dataType != DataType::UNKNOWN && "Data type must be valid (not UNKNOWN)");
		assert(data != nullptr && "Data pointer cannot be null");

		// Set the entrie buffer to the given data
		glClearNamedBufferData(id, static_cast<GLenum>(internalFormat), static_cast<GLenum>(format), static_cast<GLenum>(dataType), data);
	}
	void Buffer::subclear(Format internalFormat, long long offset, long long size, Format format, DataType dataType, const void* data) {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(internalFormat != Format::UNKNOWN && "Internal format must be valid (not UNKNOWN)");
		assert(offset >= 0LL && "Offset cannot be negative");
		assert(size >= 0LL && "Size cannot be negative");
		assert(format != Format::UNKNOWN && "Format must be valid (not UNKNOWN)");
		assert(dataType != DataType::UNKNOWN && data != nullptr && "Data type must be valid and data pointer cannot be null");

		// Set the specified buffer region to the specified data
		glClearNamedBufferSubData(id, static_cast<GLenum>(internalFormat), offset, size, static_cast<GLenum>(format), static_cast<GLenum>(dataType), data);
	}
	void* Buffer::map(long long offset, long long length, AccessFlag accessFlag) {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");
		assert(offset >= 0LL && "Offset cannot be negative");

		if (length == -1) // -1 means match to memorySize
			length = memorySize - offset; // Update length to match memorySize

		// Error check with verbose asserts
		assert(offset + length <= memorySize && "Mapping range exceeds buffer size");

		return glMapNamedBufferRange(id, offset, length, static_cast<GLbitfield>(accessFlag));
	}
	bool Buffer::unmap() {
		// Error check with verbose asserts
		assert(id != 0U && "Buffer must be valid (id != 0)");

		// Unmap data (upload data to buffer in GPU)
		return glUnmapNamedBuffer(id) == GL_TRUE;
	}
	void* Buffer::persistentMap(AccessFlag accessFlags) {
		return map(0, memorySize, accessFlags);
	}
	void Buffer::flushPersistentMap(long long offset, long long length) {
		glFlushMappedNamedBufferRange(id, offset, length);
	}
	void Buffer::invalidate() {
		glInvalidateBufferData(id);
	}
	void Buffer::invalidateRange(long long offset, long long size) {
		glInvalidateBufferSubData(id, offset, size);
	}
	long long Buffer::getParameter(ParameterName parameterName) const {
		long long value = 0;
		glGetNamedBufferParameteri64v(id, static_cast<GLenum>(parameterName), &value);
		return value;
	}
	void Buffer::setLabel(const std::string& label) {
		glObjectLabel(GL_BUFFER, id, (GLsizei)label.size(), label.c_str());
	}
	bool Buffer::isBuffer() const {
		return glIsBuffer(id);
	}
}
