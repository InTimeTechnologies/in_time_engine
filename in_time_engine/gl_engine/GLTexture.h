#pragma once

// Dependencies | std
#include <vector>
#include <memory>

// Dependencies | gl_engine
#include "GLHeader.h"

// Dependencies | glm
#include <glm/glm.hpp>

namespace gl {
    // Forward declarations
    class Engine;
    class TextureSystem;

	namespace texture {
		// Enum | texture types
		enum class Type {
			UNKNOWN = -1,

			TEXTURE_1D = GL_TEXTURE_1D,
			TEXTURE_2D = GL_TEXTURE_2D,
			TEXTURE_3D = GL_TEXTURE_3D,
			TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
			TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
			TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
			TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
			TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
			TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
			TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
			TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
		};
		// Enum | Internal format (how GPU stores the texture)
		enum class InternalFormat {
			UNKNOWN = -1,

			R8 = GL_R8,
			RG8 = GL_RG8,
			RGB8 = GL_RGB8,
			RGBA8 = GL_RGBA8,
			SRGB8 = GL_SRGB8,
			SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,

			R16F = GL_R16F,
			RG16F = GL_RG16F,
			RGB16F = GL_RGB16F,
			RGBA16F = GL_RGBA16F,

			R32F = GL_R32F,
			RG32F = GL_RG32F,
			RGB32F = GL_RGB32F,
			RGBA32F = GL_RGBA32F,

			DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
			DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
			DEPTH_COMPONENT32 = GL_DEPTH_COMPONENT32,
			DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F,
			DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
			DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8
		};
		// Enum | CPU pixel format (input data layout)
		enum class CPUPixelFormat {
			UNKNOWN = -1,

			RED = GL_RED,
			RG = GL_RG,
			RGB = GL_RGB,
			BGR = GL_BGR,
			RGBA = GL_RGBA,
			BGRA = GL_BGRA,
			DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
			STENCIL_INDEX = GL_STENCIL_INDEX,
			DEPTH_STENCIL = GL_DEPTH_STENCIL
		};
		// Enum | CPU pixel data type (data type of each channel)
		enum class CPUPixelDataType {
			UNKNOWN = -1,

			UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
			BYTE = GL_BYTE,
			UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
			SHORT = GL_SHORT,
			UNSIGNED_INT = GL_UNSIGNED_INT,
			INT = GL_INT,
			FLOAT = GL_FLOAT,
			UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
			UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
			UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
			UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
			UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
			UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2
		};
		// Enum | Texture wrap and filter modes
		enum class Wrap {
			UNKNOWN = -1,

			REPEAT = GL_REPEAT,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
			MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
		};
		enum class Filter {
			UNKNOWN = -1,

			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR,
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
		};
		enum class CompressedFormat {
			UNKNOWN = -1,

			// Compressed formats | S3TC / DXT (BC1-BC3)
			COMPRESSED_RGB_S3TC_DXT1_EXT = GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
			COMPRESSED_RGBA_S3TC_DXT1_EXT = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
			COMPRESSED_RGBA_S3TC_DXT3_EXT = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
			COMPRESSED_RGBA_S3TC_DXT5_EXT = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
			COMPRESSED_SRGB_S3TC_DXT1_EXT = GL_COMPRESSED_SRGB_S3TC_DXT1_EXT,
			COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT,
			COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT,
			COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT,

			// Compressed formats | RGTC / BC4-BC5 (single and two-channel)
			COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1,
			COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1,
			COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2,
			COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2,

			// Compressed formats | BPTC / BC6-BC7 (high-quality HDR & LDR)
			COMPRESSED_RGBA_BPTC_UNORM = GL_COMPRESSED_RGBA_BPTC_UNORM,
			COMPRESSED_SRGB_ALPHA_BPTC_UNORM = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM,
			COMPRESSED_RGB_BPTC_SIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT,
			COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT,

			// Compressed formats | ETC / ETC2 / EAC (OpenGL ES & modern desktop & mobile)
			COMPRESSED_RGB8_ETC2 = GL_COMPRESSED_RGB8_ETC2,
			COMPRESSED_SRGB8_ETC2 = GL_COMPRESSED_SRGB8_ETC2,
			COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 = GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
			COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 = GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
			COMPRESSED_RGBA8_ETC2_EAC = GL_COMPRESSED_RGBA8_ETC2_EAC,
			COMPRESSED_SRGB8_ALPHA8_ETC2_EAC = GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,

			COMPRESSED_R11_EAC = GL_COMPRESSED_R11_EAC,
			COMPRESSED_SIGNED_R11_EAC = GL_COMPRESSED_SIGNED_R11_EAC,
			COMPRESSED_RG11_EAC = GL_COMPRESSED_RG11_EAC,
			COMPRESSED_SIGNED_RG11_EAC = GL_COMPRESSED_SIGNED_RG11_EAC,

			// Compressed formats | ASTC (Adaptive Scalable Texture Compression)
			COMPRESSED_RGBA_ASTC_4x4_KHR = GL_COMPRESSED_RGBA_ASTC_4x4_KHR,
			COMPRESSED_RGBA_ASTC_5x4_KHR = GL_COMPRESSED_RGBA_ASTC_5x4_KHR,
			COMPRESSED_RGBA_ASTC_5x5_KHR = GL_COMPRESSED_RGBA_ASTC_5x5_KHR,
			COMPRESSED_RGBA_ASTC_6x5_KHR = GL_COMPRESSED_RGBA_ASTC_6x5_KHR,
			COMPRESSED_RGBA_ASTC_6x6_KHR = GL_COMPRESSED_RGBA_ASTC_6x6_KHR,
			COMPRESSED_RGBA_ASTC_8x5_KHR = GL_COMPRESSED_RGBA_ASTC_8x5_KHR,
			COMPRESSED_RGBA_ASTC_8x6_KHR = GL_COMPRESSED_RGBA_ASTC_8x6_KHR,
			COMPRESSED_RGBA_ASTC_8x8_KHR = GL_COMPRESSED_RGBA_ASTC_8x8_KHR,
			COMPRESSED_RGBA_ASTC_10x5_KHR = GL_COMPRESSED_RGBA_ASTC_10x5_KHR,
			COMPRESSED_RGBA_ASTC_10x6_KHR = GL_COMPRESSED_RGBA_ASTC_10x6_KHR,
			COMPRESSED_RGBA_ASTC_10x8_KHR = GL_COMPRESSED_RGBA_ASTC_10x8_KHR,
			COMPRESSED_RGBA_ASTC_10x10_KHR = GL_COMPRESSED_RGBA_ASTC_10x10_KHR,
			COMPRESSED_RGBA_ASTC_12x10_KHR = GL_COMPRESSED_RGBA_ASTC_12x10_KHR,
			COMPRESSED_RGBA_ASTC_12x12_KHR = GL_COMPRESSED_RGBA_ASTC_12x12_KHR,

			COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR,
			COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR
		};
		enum class ComparisonMode {
			UNKNOWN = -1,

			// Texture comparison modes
			NONE = GL_NONE,
			REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE,

			// Depth comparison functions
			LEQUAL = GL_LEQUAL,
			GEQUAL = GL_GEQUAL,
			LESS = GL_LESS,
			GREATER = GL_GREATER,
			EQUAL = GL_EQUAL,
			NOTEQUAL = GL_NOTEQUAL,
			ALWAYS = GL_ALWAYS,
			NEVER = GL_NEVER
		};

		// Functions | Enum validation
		inline bool validateType(Type textureType) {
			switch (textureType) {
				case Type::TEXTURE_1D:
				case Type::TEXTURE_2D:
				case Type::TEXTURE_3D:
				case Type::TEXTURE_1D_ARRAY:
				case Type::TEXTURE_2D_ARRAY:
				case Type::TEXTURE_RECTANGLE:
				case Type::TEXTURE_CUBE_MAP:
				case Type::TEXTURE_CUBE_MAP_ARRAY:
				case Type::TEXTURE_BUFFER:
				case Type::TEXTURE_2D_MULTISAMPLE:
				case Type::TEXTURE_2D_MULTISAMPLE_ARRAY:
					return true;
				case Type::UNKNOWN:
				default:
					return false;
			}
		}
		inline bool validateInternalFormat(InternalFormat internalFormat) {
			switch (internalFormat) {
				case InternalFormat::R8:
				case InternalFormat::RG8:
				case InternalFormat::RGB8:
				case InternalFormat::RGBA8:
				case InternalFormat::SRGB8:
				case InternalFormat::SRGB8_ALPHA8:
				case InternalFormat::R16F:
				case InternalFormat::RG16F:
				case InternalFormat::RGB16F:
				case InternalFormat::RGBA16F:
				case InternalFormat::R32F:
				case InternalFormat::RG32F:
				case InternalFormat::RGB32F:
				case InternalFormat::RGBA32F:
				case InternalFormat::DEPTH_COMPONENT16:
				case InternalFormat::DEPTH_COMPONENT24:
				case InternalFormat::DEPTH_COMPONENT32:
				case InternalFormat::DEPTH_COMPONENT32F:
				case InternalFormat::DEPTH24_STENCIL8:
				case InternalFormat::DEPTH32F_STENCIL8:
					return true;
				case InternalFormat::UNKNOWN:
				default:
					return false;
			}
		}
		inline bool validateInputPixelFormat(CPUPixelFormat inputPixelFormat) {
			switch (inputPixelFormat) {
				case CPUPixelFormat::RED:
				case CPUPixelFormat::RG:
				case CPUPixelFormat::RGB:
				case CPUPixelFormat::BGR:
				case CPUPixelFormat::RGBA:
				case CPUPixelFormat::BGRA:
				case CPUPixelFormat::DEPTH_COMPONENT:
				case CPUPixelFormat::STENCIL_INDEX:
				case CPUPixelFormat::DEPTH_STENCIL:
					return true;
				case CPUPixelFormat::UNKNOWN:
				default:
					return false;
			}
		}
		inline bool validateInputPixelDataType(CPUPixelDataType inputPixelDataType) {
			switch (inputPixelDataType) {
				case CPUPixelDataType::UNSIGNED_BYTE:
				case CPUPixelDataType::BYTE:
				case CPUPixelDataType::UNSIGNED_SHORT:
				case CPUPixelDataType::SHORT:
				case CPUPixelDataType::UNSIGNED_INT:
				case CPUPixelDataType::INT:
				case CPUPixelDataType::FLOAT:
				case CPUPixelDataType::UNSIGNED_BYTE_3_3_2:
				case CPUPixelDataType::UNSIGNED_SHORT_5_6_5:
				case CPUPixelDataType::UNSIGNED_SHORT_4_4_4_4:
				case CPUPixelDataType::UNSIGNED_SHORT_5_5_5_1:
				case CPUPixelDataType::UNSIGNED_INT_8_8_8_8:
				case CPUPixelDataType::UNSIGNED_INT_10_10_10_2:
					return true;
				case CPUPixelDataType::UNKNOWN:
				default:
					return false;
			}
		}
		inline bool validateWrap(Wrap wrap) {
			switch (wrap) {
				case Wrap::REPEAT:
				case Wrap::MIRRORED_REPEAT:
				case Wrap::CLAMP_TO_EDGE:
				case Wrap::CLAMP_TO_BORDER:
				case Wrap::MIRROR_CLAMP_TO_EDGE:
					return true;
				case Wrap::UNKNOWN:
				default:
					return false;
			}
		}
		inline bool validateFilter(Filter filter) {
			switch (filter) {
				case Filter::NEAREST:
				case Filter::LINEAR:
				case Filter::NEAREST_MIPMAP_NEAREST:
				case Filter::LINEAR_MIPMAP_NEAREST:
				case Filter::NEAREST_MIPMAP_LINEAR:
				case Filter::LINEAR_MIPMAP_LINEAR:
					return true;
				case Filter::UNKNOWN:
				default:
					return false;
			}
		}
		inline bool validateCompressedFormat(CompressedFormat compressedFormat) {
			switch (compressedFormat) {
				case CompressedFormat::COMPRESSED_RGB_S3TC_DXT1_EXT:
				case CompressedFormat::COMPRESSED_RGBA_S3TC_DXT1_EXT:
				case CompressedFormat::COMPRESSED_RGBA_S3TC_DXT3_EXT:
				case CompressedFormat::COMPRESSED_RGBA_S3TC_DXT5_EXT:
				case CompressedFormat::COMPRESSED_SRGB_S3TC_DXT1_EXT:
				case CompressedFormat::COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
				case CompressedFormat::COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
				case CompressedFormat::COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
				case CompressedFormat::COMPRESSED_RED_RGTC1:
				case CompressedFormat::COMPRESSED_SIGNED_RED_RGTC1:
				case CompressedFormat::COMPRESSED_RG_RGTC2:
				case CompressedFormat::COMPRESSED_SIGNED_RG_RGTC2:
				case CompressedFormat::COMPRESSED_RGBA_BPTC_UNORM:
				case CompressedFormat::COMPRESSED_SRGB_ALPHA_BPTC_UNORM:
				case CompressedFormat::COMPRESSED_RGB_BPTC_SIGNED_FLOAT:
				case CompressedFormat::COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT:
				case CompressedFormat::COMPRESSED_RGB8_ETC2:
				case CompressedFormat::COMPRESSED_SRGB8_ETC2:
				case CompressedFormat::COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
				case CompressedFormat::COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
				case CompressedFormat::COMPRESSED_RGBA8_ETC2_EAC:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
				case CompressedFormat::COMPRESSED_R11_EAC:
				case CompressedFormat::COMPRESSED_SIGNED_R11_EAC:
				case CompressedFormat::COMPRESSED_RG11_EAC:
				case CompressedFormat::COMPRESSED_SIGNED_RG11_EAC:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_4x4_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_5x4_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_5x5_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_6x5_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_6x6_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_8x5_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_8x6_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_8x8_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_10x5_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_10x6_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_10x8_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_10x10_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_12x10_KHR:
				case CompressedFormat::COMPRESSED_RGBA_ASTC_12x12_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR:
				case CompressedFormat::COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR:
					return true;
				case CompressedFormat::UNKNOWN:
				default:
					return false;
			}
		}
		inline bool validateComparisonMode(ComparisonMode comparisonMode) {
			switch (comparisonMode) {
				case ComparisonMode::NONE:
				case ComparisonMode::REF_TO_TEXTURE:
				case ComparisonMode::LEQUAL:
				case ComparisonMode::GEQUAL:
				case ComparisonMode::LESS:
				case ComparisonMode::GREATER:
				case ComparisonMode::EQUAL:
				case ComparisonMode::NOTEQUAL:
				case ComparisonMode::ALWAYS:
				case ComparisonMode::NEVER:
					return true;
				case ComparisonMode::UNKNOWN:
				default:
					return false;
			}
		}

		// classes
		class Texture2D {
			// Static
			private:
				// Properties
				static Wrap s_defaultWrapS;
				static Wrap s_defaultWrapT;
				static Filter s_defaultMinFilter;
				static Filter s_defaultMagFilter;

				static InternalFormat s_defaultInternalFormat;
				static CPUPixelFormat s_defaultCPUInputPixelFormat;
				static CPUPixelDataType s_defaultCPUInputPixelDataType;

			public:
				// Getters
				static Wrap s_getDefaultWrapS();
				static Wrap s_getDefaultWrapT();
				static Filter s_getDefaultMinFilter();
				static Filter s_getDefaultMagFilter();

				static InternalFormat s_getDefaultInternalFormat();
				static CPUPixelFormat s_getDefaultCPUInputPixelFormat();
				static CPUPixelDataType s_getDefaultCPUInputPixelDataType();

				// Setters
				static void s_setDefaultWrapS(Wrap wrapS = Wrap::REPEAT);
				static void s_setDefaultWrapT(Wrap wrapT = Wrap::REPEAT);
				static void s_setDefaultFilterMin(Filter minFilter = Filter::LINEAR_MIPMAP_LINEAR);
				static void s_setDefaultFilterMag(Filter magFilter = Filter::LINEAR);

				static void s_setDefaultInternalFormat(InternalFormat internalFormat = InternalFormat::RGBA8);
				static void s_setDefaultCPUInputPixelFormat(CPUPixelFormat cpuInputPixelFormat = CPUPixelFormat::RGBA);
				static void s_setDefaultCPUInputPixelDataType(CPUPixelDataType cpiInputPixelDataType = CPUPixelDataType::UNSIGNED_BYTE);

			// Object
			private:
				// Properties
				unsigned int id{ 0U };

				InternalFormat internalFormat{ InternalFormat::UNKNOWN };
				int width{ 0 };
				int height{ 0 };
				unsigned int mipmaps{ 1U };

				Wrap wrapS{ Wrap::UNKNOWN };
				Wrap wrapT{ Wrap::UNKNOWN };
				Filter minFilter{ Filter::UNKNOWN };
				Filter magFilter{ Filter::UNKNOWN };

				glm::vec4 borderColor{ 0.0f, 0.0f, 0.0f, 0.0f };

				float minLOD{ 1000.0f };
				float maxLOD{ -1000.0f };
				float lodBias{ 0.0f };

				ComparisonMode comparisonMode{ ComparisonMode::NONE };
				ComparisonMode comparisonFunc{ ComparisonMode::LEQUAL };

				std::shared_ptr<Texture2D*> selfSharedPointer{ std::make_shared<Texture2D*>(this) };

			public:
				// Constructor / Destructor
				Texture2D();
				Texture2D(unsigned int mipmaps, InternalFormat internalFormat, int width, int height);
				Texture2D(unsigned int mipmaps, InternalFormat internalFormat, int width, int height, unsigned int mipmapLevel, CPUPixelFormat inputPixelFormat, CPUPixelDataType inputPixelDataType, const void* data);
				Texture2D(const texture::Texture2D& other);
				Texture2D(texture::Texture2D&& other) noexcept;
				~Texture2D();

				// Operators | assignment
				texture::Texture2D& operator=(const texture::Texture2D& other);
				texture::Texture2D& operator=(texture::Texture2D&& other) noexcept;

				// Operators | equality
				bool operator==(const Texture2D& other) const;

				// Getters
				unsigned int getID() const;

				Wrap getWrapS() const;
				Wrap getWrapT() const;
				Filter getFilterMin() const;
				Filter getFilterMag() const;
				int getWidth() const;
				int getHeight() const;
				unsigned int getMipmaps() const;
				float getAspectRatio() const;
				InternalFormat getInternalFormat() const;
				glm::vec4 getBorderColor() const;
				float getMinLOD() const;
				float getMaxLOD() const;
				float getLODBias() const;
				ComparisonMode getComparisonMode() const;
				ComparisonMode getComparisonFunc() const;
				std::vector<unsigned char> getData(unsigned int mipmapLevel, CPUPixelFormat cpuPixelFormat, CPUPixelDataType cpuPixelDataType) const;

				std::weak_ptr<Texture2D*> getWeakPointer() const;

				// Setters
				bool setWrap(Wrap wrapS = Wrap::REPEAT, Wrap wrapT = Wrap::REPEAT);
				bool setWrapS(Wrap wrapS = Wrap::REPEAT);
				bool setWrapT(Wrap wrapT = Wrap::REPEAT);
				bool setFilter(Filter minFilter = Filter::LINEAR_MIPMAP_LINEAR, Filter magFilter = Filter::LINEAR);
				bool setFilterMin(Filter minFilter = Filter::LINEAR_MIPMAP_LINEAR);
				bool setFilterMag(Filter magFilter = Filter::LINEAR); // nearest or linear
				bool setBorderColor(const glm::vec4& borderColor);
				bool setLOD(float minLOD, float maxLOD, float lodBias);
				bool setMinLOD(float minLOD);
				bool setMaxLOD(float maxLOD);
				bool setLODBias(float lodBias);
				bool setComparisonMode(ComparisonMode comparisonMode = ComparisonMode::NONE, ComparisonMode comparisonFunc = ComparisonMode::LEQUAL);
				bool setComparisonMode(ComparisonMode comparisonMode = ComparisonMode::NONE);
				bool setComparisonFunc(ComparisonMode comparisonFunc = ComparisonMode::LEQUAL);

				// Functions
				void allocate(unsigned int mipmaps, InternalFormat internalFormat, int width, int height);
				void free();
				bool load(unsigned int mipmapLevel, int x, int y, int width, int height, CPUPixelFormat format, CPUPixelDataType type, const void* data);
				void copy(const Texture2D& other);

				bool generateMipmaps();

				void bindToSlot(int slotNumber) const;
		};
	}
}
