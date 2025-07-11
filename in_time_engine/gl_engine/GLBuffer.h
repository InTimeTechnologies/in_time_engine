#pragma once

// Dependencies | glew
#include <glew/glew.h>

// Dependencies | glfw
#include <glfw/glfw3.h>

// Dependencies | OpenGLEngine
#include "GLBufferType.h"
#include "GLBufferUsage.h"

namespace gl {
	class Buffer {
		// Static
		private:
			// Properties
			static BufferType defaultBufferType;
			static BufferUsage defaultBufferUsage;

			// Functions | Helpers
			static bool validateBufferType(BufferType glslBufferType);
			static bool validateBufferUsage(BufferUsage glslBufferUsage);

		public:
			// Getters
			static BufferType getDefaultBufferType();
			static BufferUsage getDefautBufferUsage();

			// Setters
			static void setDefaultBufferType(BufferType bufferType);
			static void setDefaultBufferUsage(BufferUsage bufferUsage);

			// Functions
			static void unbind(BufferType type);
			static void unbindAll();
			static bool isBuffer(unsigned int id);

		// Object
		private:
			// Properties
			unsigned int id = 0;
			BufferType intendedUse = defaultBufferType;
			BufferUsage usage = defaultBufferUsage;
			long long memorySize = 0LL;

		public:
			// Constructors / Destructor
			Buffer();
			Buffer(BufferType type, BufferUsage usage, long long memorySize, void* data);
			Buffer(BufferType type, BufferUsage usage, long long memorySize);
			~Buffer();

			// Getters
			unsigned int getID() const;
			long long size() const;
			BufferType getBufferType() const;
			BufferUsage getBufferUsage() const;

			// Functions
			bool bind() const;
			void bind(BufferType type) const;
			void bindBufferBase(int bindingPoint) const;
			void bindBufferBase(BufferType glslBufferType, int bindingPoint) const;
			void bindVertexBuffer(unsigned int bindingIndex, int offset, int stride) const;
			void unbindVertexBuffer(unsigned int bindingIndex) const;
			void getData(void* data) const;
			void getData(long long offset, long long size, void* data) const;
			bool write(long long memorySize, const void* data, BufferUsage usage);
			bool subwrite(long long offset, long long size, const void* data);
			bool copy(Buffer* glslBuffer);
			bool subCopy(Buffer* glslBuffer, long long readOffset, long long writeOffset, int size);
			bool isBuffer();
	};
}

/* Supported buffer types
 * 
 * GL_ARRAY_BUFFER,
 * GL_ATOMIC_COUNTER_BUFFER,
 * GL_COPY_READ_BUFFER,
 * GL_COPY_WRITE_BUFFER,
 * GL_DISPATCH_INDIRECT_BUFFER,
 * GL_DRAW_INDIRECT_BUFFER,
 * GL_ELEMENT_ARRAY_BUFFER,
 * GL_PIXEL_PACK_BUFFER,
 * GL_PIXEL_UNPACK_BUFFER,
 * GL_QUERY_BUFFER,
 * GL_SHADER_STORAGE_BUFFER,
 * GL_TEXTURE_BUFFER,
 * GL_TRANSFORM_FEEDBACK_BUFFER,
 * GL_UNIFORM_BUFFER
 */

/* Supported buffer usages
 * 
 * GL_STREAM_DRAW,
 * GL_STREAM_READ,
 * GL_STREAM_COPY,
 * GL_STATIC_DRAW,
 * GL_STATIC_READ,
 * GL_STATIC_COPY,
 * GL_DYNAMIC_DRAW,
 * GL_DYNAMIC_READ,
 * GL_DYNAMIC_COPY
 */

/* Deprecated | Reason: lower memory consumption and eliminate data redundancy
enum class BufferType {
	VERTEX             = GL_ARRAY_BUFFER,
	ATOMIC_COUNTER     = GL_ATOMIC_COUNTER_BUFFER,
	COPY_READ          = GL_COPY_READ_BUFFER,
	COPY_WRITE         = GL_COPY_WRITE_BUFFER,
	DIPSATCH_INDIRECT  = GL_DISPATCH_INDIRECT_BUFFER,
	DRAW_INDIRECT      = GL_DRAW_INDIRECT_BUFFER,
	INDEX              = GL_ELEMENT_ARRAY_BUFFER,
	PIXEL_PACK         = GL_PIXEL_PACK_BUFFER,
	PIXEL_UNPACK       = GL_PIXEL_UNPACK_BUFFER,
	QUERY              = GL_QUERY_BUFFER,
	SHADER_STORAGE     = GL_SHADER_STORAGE_BUFFER,
	TEXTURE            = GL_TEXTURE_BUFFER,
	TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
	UNIFORM            = GL_UNIFORM_BUFFER
};

enum class GLSLBufferUsage {
	STREAM_DRAW  = GL_STREAM_DRAW,
	STREAM_READ  = GL_STREAM_READ,
	STREAM_COPY  = GL_STREAM_COPY,
	STATIC_DRAW  = GL_STATIC_DRAW,
	STATIC_READ  = GL_STATIC_READ,
	STATIC_COPY  = GL_STATIC_COPY,
	DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
	DYNAMIC_READ = GL_DYNAMIC_READ,
	DYNAMIC_COPY = GL_DYNAMIC_COPY
};
*/
