#pragma once

// Dependencies | std
#include <list>
#include <string>

// Dependencies | gl_engine
#include "GLHeader.h"

namespace gl {
	class Buffer {
		public:
			// Scoped enums
			enum class Type : unsigned int {
				UNKNOWN = 0U,

				VERTEX_BUFFER = GL_ARRAY_BUFFER,
				ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
				COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
				COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
				DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
				DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
				INDEX_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
				PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
				PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
				QUERY_BUFFER = GL_QUERY_BUFFER,
				SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
				TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
				TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
				UNIFORM_BUFFER = GL_UNIFORM_BUFFER
			};
			enum class Format : unsigned int {
				UNKNOWN = 0U,

				R8 = GL_R8,
				R16 = GL_R16,
				R16F = GL_R16F,
				R32F = GL_R32F,
				R8I = GL_R8I,
				R16I = GL_R16I,
				R32I = GL_R32I,
				R8UI = GL_R8UI,
				R16UI = GL_R16UI,
				R32UI = GL_R32UI,
				RG8 = GL_RG8,
				RG16 = GL_RG16,
				RG16F = GL_RG16F,
				RG32F = GL_RG32F,
				RG8I = GL_RG8I,
				RG16I = GL_RG16I,
				RG32I = GL_RG32I,
				RG8UI = GL_RG8UI,
				RG16UI = GL_RG16UI,
				RG32UI = GL_RG32UI,
				RGB8 = GL_RGB8,
				SRGB8 = GL_SRGB8,
				RGB16 = GL_RGB16,
				RGB16F = GL_RGB16F,
				RGB32F = GL_RGB32F,
				RGB8I = GL_RGB8I,
				RGB16I = GL_RGB16I,
				RGB32I = GL_RGB32I,
				RGB8UI = GL_RGB8UI,
				RGB16UI = GL_RGB16UI,
				RGB32UI = GL_RGB32UI,
				RGBA8 = GL_RGBA8,
				SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
				RGBA16 = GL_RGBA16,
				RGBA16F = GL_RGBA16F,
				RGBA32F = GL_RGBA32F,
				RGBA8I = GL_RGBA8I,
				RGBA16I = GL_RGBA16I,
				RGBA32I = GL_RGBA32I,
				RGBA8UI = GL_RGBA8UI,
				RGBA16UI = GL_RGBA16UI,
				RGBA32UI = GL_RGBA32UI,
				DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
				DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
				DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F
			};
			enum class DataType : unsigned int {
				UNKNOWN = 0U,
				BYTE = GL_BYTE,
				UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
				SHORT = GL_SHORT,
				UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
				INT = GL_INT,
				UNSIGNED_INT = GL_UNSIGNED_INT,
				FLOAT = GL_FLOAT,
				HALF_FLOAT = GL_HALF_FLOAT,
				DOUBLE = GL_DOUBLE
			};
			enum class ParameterName : unsigned int {
				UNKNOWN = 0U,

				BUFFER_ACCESS = GL_BUFFER_ACCESS,
				BUFFER_ACCESS_FLAGS = GL_BUFFER_ACCESS_FLAGS,
				BUFFER_MMUTABLE_STORAGE = GL_BUFFER_IMMUTABLE_STORAGE,
				BUFFER_MAPPED = GL_BUFFER_MAPPED,
				BUFFER_MAP_LENGTH = GL_BUFFER_MAP_LENGTH,
				BUFFER_MAP_OFFSET = GL_BUFFER_MAP_OFFSET,
				BUFFER_SIZE = GL_BUFFER_SIZE,
				BUFFER_STORAGE_FLAGS = GL_BUFFER_STORAGE_FLAGS,
				BUFFER_USAGE = GL_BUFFER_USAGE
			};
			enum class DataStoreUsage : unsigned int {
				UNKNOWN = 0U,

				DYNAMIC_STORAGE = GL_DYNAMIC_STORAGE_BIT,			// The contents of the data store may be updated after creation through calls to glBufferSubData. If this bit is not set, the buffer content may not be directly updated by the client. The data argument may be used to specify the initial content of the buffer's data store regardless of the presence of the GL_DYNAMIC_STORAGE_BIT. Regardless of the presence of this bit, buffers may always be updated with server-side calls such as glCopyBufferSubData and glClearBufferSubData.
				MAP_READ = GL_MAP_READ_BIT,							// The data store may be mapped by the client for read access and a pointer in the client's address space obtained that may be read from.
				MAP_WRITE = GL_MAP_WRITE_BIT,						// The data store may be mapped by the client for write access and a pointer in the client's address space obtained that may be written through.
				MAP_PERSISTENT = GL_MAP_PERSISTENT_BIT,				// The client may request that the server read from or write to the buffer while it is mapped. The client's pointer to the data store remains valid so long as the data store is mapped, even during execution of drawing or dispatch commands.
				MAP_COHERENT = GL_MAP_COHERENT_BIT,					// Shared access to buffers that are simultaneously mapped for client access and are used by the server will be coherent, so long as that mapping is performed using glMapBufferRange. That is, data written to the store by either the client or server will be immediately visible to the other with no further action taken by the application. Refer to documentation for more details.
				CLIENT_STORAGE = GL_CLIENT_STORAGE_BIT				// When all other criteria for the buffer storage allocation are met, this bit may be used by an implementation to determine whether to use storage that is local to the server or to the client to serve as the backing store for the buffer.
			};
			enum class AccessFlag : unsigned int {
				UNKNOWN = 0U,

				READ = GL_MAP_READ_BIT,								// Allow reading
				WRITE = GL_MAP_WRITE_BIT,							// Allow writing
				INVALIDATE_RANGE = GL_MAP_INVALIDATE_RANGE_BIT,		// Discard previous contents of the range
				INVALIDATE_BUFFER = GL_MAP_INVALIDATE_BUFFER_BIT,	// Discard previous contents of the entire buffer
				UNSYNCHRONIZED = GL_MAP_UNSYNCHRONIZED_BIT,			// Avoid GPU synchronization
				PERSISTENT = GL_MAP_PERSISTENT_BIT,					// Mapping persists across frames
				COHERENT = GL_MAP_COHERENT_BIT,						// Ensure CPU/GPU memory coherency
				FLUSH_EXPLICIT = GL_MAP_FLUSH_EXPLICIT_BIT			// Explicit flush required for persistent mapping
			};

			// Scopred enum bitwise operations | DataStorageUsage
			friend inline DataStoreUsage operator|(DataStoreUsage lhs, DataStoreUsage rhs) {
				return static_cast<DataStoreUsage>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs));
			}
			friend inline DataStoreUsage operator&(DataStoreUsage lhs, DataStoreUsage rhs) {
				return static_cast<DataStoreUsage>(static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs));
			}
			friend inline DataStoreUsage& operator|=(DataStoreUsage& lhs, DataStoreUsage rhs) {
				lhs = lhs | rhs;
				return lhs;
			}
			friend inline DataStoreUsage& operator&=(DataStoreUsage& lhs, DataStoreUsage rhs) {
				lhs = lhs & rhs;
				return lhs;
			}

			// Scoped enum bitwise operations | AccessFlag
			friend inline AccessFlag operator|(AccessFlag a, AccessFlag b) {
				return static_cast<AccessFlag>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
			}
			friend inline AccessFlag operator&(AccessFlag a, AccessFlag b) {
				return static_cast<AccessFlag>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
			}
			friend inline AccessFlag& operator|=(AccessFlag& a, AccessFlag b) {
				a = a | b;
				return a;
			}
			friend inline AccessFlag& operator&=(AccessFlag& a, AccessFlag b) {
				a = a & b;
				return a;
			}

		// Static
		public:
			// Functions
			static void s_unbind(Type type);
			static void s_unbindAll();
			static void s_unbindVertexBuffer(unsigned int bindingIndex);
			static bool s_isBuffer(unsigned int id);

		// Object
		private:
			// Properties
			unsigned int id{ 0U };
			long long memorySize{ 0LL };
			Type type{ Type::UNKNOWN };
			DataStoreUsage dataStoreUsage{ DataStoreUsage::UNKNOWN };

		public:
			// Constructors / Destructor
			Buffer() = default;
			Buffer(long long memorySize);
			Buffer(long long memorySize, void* data);
			Buffer(long long memorySize, void* data, Type type);
			Buffer(const Buffer& other);
			Buffer(Buffer&& other) noexcept;
			~Buffer();

			// Operator | assignment
			Buffer& operator=(const Buffer& other);
			Buffer& operator=(Buffer&& other) noexcept;

			// Getters
			unsigned int getID() const;
			long long getMemorySize() const;
			Type getType() const;

			// Setters
			void setType(Type type);

			// Functions
			void swap(Buffer&& other) noexcept;
			void allocate(long long memorySize, const void* data = nullptr, DataStoreUsage dataStoreUsage = DataStoreUsage::DYNAMIC_STORAGE | DataStoreUsage::MAP_WRITE | DataStoreUsage::MAP_READ);
			void free();
			void bind() const;
			void bind(Type type) const;
			void bindBufferBase(unsigned int bindingPoint) const;
			void bindBufferBase(Type glslBufferType, unsigned int bindingPoint) const;
			void bindVertexBuffer(unsigned int bindingIndex, long long offset, int stride) const;
			void getData(void* data) const;
			void getData(long long offset, long long size, void* data) const;
			void subwrite(long long offset, long long size, const void* data);
			void copy(const Buffer& other);
			void subCopy(const Buffer& other, long long readOffset, long long writeOffset, long long size);
			void clear(Format internalFormat, Format format, DataType dataType, const void* data);
			void subclear(Format internalFormat, long long offset, long long size, Format format, DataType dataType, const void* data);
			void* map(long long offset = 0LL, long long length = -1LL, AccessFlag accessFlag = AccessFlag::READ | AccessFlag::WRITE | AccessFlag::UNSYNCHRONIZED);
			bool unmap();
			void* persistentMap(AccessFlag accessFlags = AccessFlag::WRITE | AccessFlag::PERSISTENT | AccessFlag::COHERENT);
			void flushPersistentMap(long long offset, long long length);
			void invalidate();
			void invalidateRange(long long offset, long long size);
			long long getParameter(ParameterName parameterName) const;
			void setLabel(const std::string& label);
			bool isBuffer() const;
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
enum class Type {
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
