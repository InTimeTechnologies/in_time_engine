#include "GLTexture.h"

// Dependencies | std
#include <algorithm>

namespace gl {
	namespace texture {
		// class Texture2D

		// Static | private

		// Properties
		Wrap Texture2D::s_defaultWrapS{ Wrap::REPEAT };
		Wrap Texture2D::s_defaultWrapT{ Wrap::REPEAT };
		Filter Texture2D::s_defaultMinFilter{ Filter::LINEAR_MIPMAP_LINEAR };
		Filter Texture2D::s_defaultMagFilter{ Filter::LINEAR };

		InternalFormat Texture2D::s_defaultInternalFormat{ InternalFormat::RGBA8 };
		CPUPixelFormat Texture2D::s_defaultCPUInputPixelFormat{ CPUPixelFormat::RGBA };
		CPUPixelDataType Texture2D::s_defaultCPUInputPixelDataType{ CPUPixelDataType::UNSIGNED_BYTE };

		// Getters
		Wrap Texture2D::s_getDefaultWrapS() {
			return s_defaultWrapS;
		}
		Wrap Texture2D::s_getDefaultWrapT() {
			return s_defaultWrapT;
		}
		Filter Texture2D::s_getDefaultMinFilter() {
			return s_defaultMinFilter;
		}
		Filter Texture2D::s_getDefaultMagFilter() {
			return s_defaultMagFilter;
		}

		InternalFormat Texture2D::s_getDefaultInternalFormat() {
			return s_defaultInternalFormat;
		}
		CPUPixelFormat Texture2D::s_getDefaultCPUInputPixelFormat() {
			return s_defaultCPUInputPixelFormat;
		}
		CPUPixelDataType Texture2D::s_getDefaultCPUInputPixelDataType() {
			return s_defaultCPUInputPixelDataType;
		}

		// Setters
		void Texture2D::s_setDefaultWrapS(Wrap wrapS) {
			if (!validateWrap(wrapS))
				return;
			s_defaultWrapS = wrapS;
		}
		void Texture2D::s_setDefaultWrapT(Wrap wrapT) {
			if (!validateWrap(wrapT))
				return;
			s_defaultWrapT = wrapT;
		}
		void Texture2D::s_setDefaultFilterMin(Filter minFilter) {
			if (!validateFilter(minFilter))
				return;
			s_defaultMinFilter = minFilter;
		}
		void Texture2D::s_setDefaultFilterMag(Filter magFilter) {
			if (!validateFilter(magFilter))
				return;
			s_defaultMagFilter = magFilter;
		}

		void Texture2D::s_setDefaultInternalFormat(InternalFormat internalFormat) {
			if (!validateInternalFormat(internalFormat))
				return;
			s_defaultInternalFormat = internalFormat;
		}
		void Texture2D::s_setDefaultCPUInputPixelFormat(CPUPixelFormat cpuInputPixelFormat) {
			if (!validateInputPixelFormat(cpuInputPixelFormat))
				return;
			s_defaultCPUInputPixelFormat = cpuInputPixelFormat;
		}
		void Texture2D::s_setDefaultCPUInputPixelDataType(CPUPixelDataType cpiInputPixelDataType) {
			if (!validateInputPixelDataType(cpiInputPixelDataType))
				return;
			s_defaultCPUInputPixelDataType = cpiInputPixelDataType;
		}

		// Setters

		// Object | public

		// Constructor / Destructor
		Texture2D::Texture2D() {

		}
		Texture2D::Texture2D(unsigned int mipmaps, InternalFormat internalFormat, int width, int height) {
			// Allocate memory in GPU
			allocate(mipmaps, internalFormat, width, height);

			// Parameters | Wrap / Fileter
			setWrap(s_defaultWrapS, s_defaultWrapT);
			setFilter(s_defaultMinFilter, s_defaultMagFilter);
		}
		Texture2D::Texture2D(unsigned int mipmaps, InternalFormat internalFormat, int width, int height, unsigned int mipmapLevel, CPUPixelFormat inputPixelFormat, CPUPixelDataType cpuInputPixelDataType, const void* data) : Texture2D(mipmaps, internalFormat, width, height) {
			// Upload data to GPU texture
			load(mipmapLevel, 0, 0, width, height, inputPixelFormat, cpuInputPixelDataType, data);
		}
		Texture2D::Texture2D(const texture::Texture2D& other) {
			copy(other);
		}
		Texture2D::Texture2D(texture::Texture2D&& other) noexcept {
			if (this == &other)
				return;

			// Steal resources from other
			id = other.id;
			internalFormat = other.internalFormat;
			width = other.width;
			height = other.height;
			mipmaps = other.mipmaps;
			wrapS = other.wrapS;
			wrapT = other.wrapT;
			minFilter = other.minFilter;
			magFilter = other.magFilter;
			borderColor = other.borderColor;
			minLOD = other.minLOD;
			maxLOD = other.maxLOD;
			lodBias = other.lodBias;
			comparisonMode = other.comparisonMode;
			comparisonFunc = other.comparisonFunc;

			// Leave other in valid but empty state
			other.id = 0U;
			other.internalFormat = InternalFormat::UNKNOWN;
			other.width = 0;
			other.height = 0;
			other.mipmaps = 0U;
			other.wrapS = Wrap::UNKNOWN;
			other.wrapT = Wrap::UNKNOWN;
			other.minFilter = Filter::UNKNOWN;
			other.magFilter = Filter::UNKNOWN;
			other.borderColor = glm::vec4(0.0f);
			other.minLOD = -1000.0f;
			other.maxLOD = 1000.0f;
			other.lodBias = 0.0f;
			other.comparisonMode = ComparisonMode::NONE;
			other.comparisonFunc = ComparisonMode::LEQUAL;
		}
		Texture2D::~Texture2D() {
			// Reset properties
			free();
		}

		// Operators | assignment
		Texture2D& Texture2D::operator=(const texture::Texture2D& other) {
			if (this != &other)
				copy(other);

			return *this;
		}
		Texture2D& Texture2D::operator=(Texture2D&& other) noexcept {
			if (this != &other) {
				// Release any existing resource
				free();

				// Steal from other
				id = other.id;
				internalFormat = other.internalFormat;
				width = other.width;
				height = other.height;
				mipmaps = other.mipmaps;
				wrapS = other.wrapS;
				wrapT = other.wrapT;
				minFilter = other.minFilter;
				magFilter = other.magFilter;
				borderColor = other.borderColor;
				minLOD = other.minLOD;
				maxLOD = other.maxLOD;
				lodBias = other.lodBias;
				comparisonMode = other.comparisonMode;
				comparisonFunc = other.comparisonFunc;

				// Leave other in valid but empty state
				other.id = 0U;
				other.internalFormat = InternalFormat::UNKNOWN;
				other.width = 0;
				other.height = 0;
				other.mipmaps = 0U;
				other.wrapS = Wrap::UNKNOWN;
				other.wrapT = Wrap::UNKNOWN;
				other.minFilter = Filter::UNKNOWN;
				other.magFilter = Filter::UNKNOWN;
				other.borderColor = glm::vec4(0.0f);
				other.minLOD = -1000.0f;
				other.maxLOD = 1000.0f;
				other.lodBias = 0.0f;
				other.comparisonMode = ComparisonMode::NONE;
				other.comparisonFunc = ComparisonMode::LEQUAL;
			}
			return *this;
		}

		// Operators | equality
		bool Texture2D::operator==(const Texture2D& other) const {
			return id == other.id;
		}

		// Getters
		unsigned int Texture2D::getID() const {
			return id;
		}
		Wrap Texture2D::getWrapS() const {
			return wrapS;
		}
		Wrap Texture2D::getWrapT() const {
			return wrapT;
		}
		Filter Texture2D::getFilterMin() const {
			return minFilter;
		}
		Filter Texture2D::getFilterMag() const {
			return magFilter;
		}
		int Texture2D::getWidth() const {
			return width;
		}
		int Texture2D::getHeight() const {
			return height;
		}
		unsigned int Texture2D::getMipmaps() const {
			return mipmaps;
		}
		float Texture2D::getAspectRatio() const {
			if (height == 0)
				return 0.0f;
			return static_cast<float>(width) / static_cast<float>(height);
		}
		InternalFormat Texture2D::getInternalFormat() const {
			return internalFormat;
		}
		glm::vec4 Texture2D::getBorderColor() const {
			return borderColor;
		}
		float Texture2D::getMinLOD() const {
			return minLOD;
		}
		float Texture2D::getMaxLOD() const {
			return maxLOD;
		}
		float Texture2D::getLODBias() const {
			return lodBias;
		}
		ComparisonMode Texture2D::getComparisonMode() const {
			return comparisonMode;
		}
		ComparisonMode Texture2D::getComparisonFunc() const {
			return comparisonFunc;
		}
		std::vector<unsigned char> Texture2D::getData(unsigned int mipLevel, CPUPixelFormat cpuInputPixelFormat, CPUPixelDataType cpuInputPixelDataType) const {
			// Query width & height at this mip level
			GLint mipWidth = 0, mipHeight = 0;
			glGetTextureLevelParameteriv(id, mipLevel, GL_TEXTURE_WIDTH, &mipWidth);
			glGetTextureLevelParameteriv(id, mipLevel, GL_TEXTURE_HEIGHT, &mipHeight);

			// Figure out channel count (caller specifies the format they want)
			GLint channels = 0;
			switch (cpuInputPixelFormat) {
				case CPUPixelFormat::RED:  channels = 1; break;
				case CPUPixelFormat::RG:   channels = 2; break;
				case CPUPixelFormat::RGB:  channels = 3; break;
				case CPUPixelFormat::BGR:  channels = 3; break;
				case CPUPixelFormat::RGBA: channels = 4; break;
				case CPUPixelFormat::BGRA: channels = 4; break;
				default: channels = 4; break; // safe fallback
			}

			// Figure out bytes per channel from type
			GLint bytesPerChannel = 1;
			switch (cpuInputPixelDataType) {
				case CPUPixelDataType::UNSIGNED_BYTE:
				case CPUPixelDataType::BYTE:
					bytesPerChannel = 1; break;
				case CPUPixelDataType::UNSIGNED_SHORT:
				case CPUPixelDataType::SHORT:
					bytesPerChannel = 2; break;
				case CPUPixelDataType::UNSIGNED_INT:
				case CPUPixelDataType::INT:
				case CPUPixelDataType::FLOAT:
					bytesPerChannel = 4; break;
				default:
					bytesPerChannel = 1; break;
			}

			size_t bufferSize = static_cast<size_t>(mipWidth) * mipHeight * channels * bytesPerChannel;

			// Allocate buffer
			std::vector<unsigned char> buffer(bufferSize);

			// Fetch pixels
			glGetTextureImage(id, mipLevel, static_cast<GLenum>(cpuInputPixelFormat), static_cast<GLenum>(cpuInputPixelDataType), static_cast<GLsizei>(bufferSize), buffer.data());

			return buffer;
		}
		std::weak_ptr<Texture2D*> Texture2D::getWeakPointer() const {
			return std::weak_ptr<Texture2D*>(selfSharedPointer);
		}

		// Setters
		bool Texture2D::setWrap(Wrap wrapS, Wrap wrapT) {
			if (id == 0)
				return false; // Fail

			glTextureParameteri(id, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapS));
			glTextureParameteri(id, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapT));
			this->wrapS = wrapS;
			this->wrapT = wrapT;

			return true; // Success
		}
		bool Texture2D::setWrapS(Wrap wrapS) {
			if (id == 0)
				return false; // Fail

			glTextureParameteri(id, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrapS));
			this->wrapS = wrapS;

			return true; // Success
		}
		bool Texture2D::setWrapT(Wrap wrapT) {
			if (id == 0)
				return false; // Fail

			glTextureParameteri(id, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrapT));
			this->wrapT = wrapT;

			return true; // Success
		}
		bool Texture2D::setFilter(Filter minFilter, Filter magFilter) {
			if (id == 0)
				return false; // Fail
			glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter));
			glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter));
			this->minFilter = minFilter;
			this->magFilter = magFilter;

			return true; // Success
		}
		bool Texture2D::setFilterMin(Filter minFilter) {
			if (id == 0)
				return false; // Fail

			glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(minFilter));
			this->minFilter = minFilter;

			return true; // Success
		}
		bool Texture2D::setFilterMag(Filter magFilter) {
			if (id == 0)
				return false; // Fail

			glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(magFilter));
			this->magFilter = magFilter;

			return true; // Success
		}
		bool Texture2D::setLOD(float minLOD, float maxLOD, float lodBias) {
			if (id == 0)
				return false; // Fail
			glTextureParameterf(id, GL_TEXTURE_MIN_LOD, minLOD);
			glTextureParameterf(id, GL_TEXTURE_MAX_LOD, maxLOD);
			glTextureParameterf(id, GL_TEXTURE_LOD_BIAS, lodBias);
			return true; // Success
		}
		bool Texture2D::setMinLOD(float minLOD) {
			if (id == 0)
				return false; // Fail
			glTextureParameterf(id, GL_TEXTURE_MIN_LOD, minLOD);
			return true; // Success
		}
		bool Texture2D::setMaxLOD(float maxLOD) {
			if (id == 0)
				return false; // Fail
			glTextureParameterf(id, GL_TEXTURE_MAX_LOD, maxLOD);
			return true; // Success
		}
		bool Texture2D::setLODBias(float lodBias) {
			if (id == 0)
				return false; // Fail
			glTextureParameterf(id, GL_TEXTURE_LOD_BIAS, lodBias);
			return true; // Success
		}
		bool Texture2D::setBorderColor(const glm::vec4& borderColor) {
			if (id == 0)
				return false; // Fail

			glTextureParameterfv(id, GL_TEXTURE_BORDER_COLOR, &borderColor[0]);
			this->borderColor = borderColor;

			return true; // Success
		}
		bool Texture2D::setComparisonMode(ComparisonMode comparisonMode, ComparisonMode comparisonFunc) {
			if (id == 0)
				return false; // Fail
			glTextureParameteri(id, GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(comparisonMode));
			glTextureParameteri(id, GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(comparisonFunc));
			this->comparisonMode = comparisonMode;
			this->comparisonFunc = comparisonFunc;
			return true; // Success
		}
		bool Texture2D::setComparisonMode(ComparisonMode comparisonMode) {
			if (id == 0)
				return false; // Fail
			glTextureParameteri(id, GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(comparisonMode));
			this->comparisonMode = comparisonMode;
			return true; // Success
		}
		bool Texture2D::setComparisonFunc(ComparisonMode comparisonFunc) {
			if (id == 0)
				return false; // Fail
			glTextureParameteri(id, GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(comparisonFunc));
			this->comparisonFunc = comparisonFunc;
			return true; // Success
		}

		// Functions
		void Texture2D::allocate(unsigned int mipmaps, InternalFormat internalFormat, int width, int height) {
			free();

			glGenTextures(1, &id);
			if (mipmaps == 0)
				mipmaps = 1;
			glTextureStorage2D(id, mipmaps, static_cast<GLenum>(internalFormat), width, height);

			this->mipmaps = mipmaps;
			this->internalFormat = internalFormat;
			this->width = width;
			this->height = height;
		}
		void Texture2D::free() {
			if (id > 0) {
				// Delete texture from GPU
				glDeleteTextures(1, &id);
				id = 0;
			}

			// Reset properties
			wrapS = Wrap::UNKNOWN;
			wrapT = Wrap::UNKNOWN;
			minFilter = Filter::UNKNOWN;
			magFilter = Filter::UNKNOWN;
			mipmaps = 1U;
			width = 0;
			height = 0;
			internalFormat = InternalFormat::UNKNOWN;
		}
		bool Texture2D::load(unsigned int mipmapLevel, int x, int y, int width, int height, CPUPixelFormat format, CPUPixelDataType type, const void* data) {
			// Error check
			if (id == 0 || mipmapLevel >= this->mipmaps || x < 0 || y < 0 || width < 0 || height < 0 || x + width > this->width || y + height > this->height || data == nullptr)
				return false; // Fail

			glTextureSubImage2D(id, mipmapLevel, x, y, width, height, static_cast<GLenum>(format), static_cast<GLenum>(type), data);

			return true; // Success
		}
		void Texture2D::copy(const Texture2D& other) {
			// Create empty texture with the same size and format as 'other'
			allocate(other.mipmaps, other.internalFormat, other.width, other.height);

			// Copy data from 'other' to this texture
			for (unsigned int level = 0; level < other.mipmaps; ++level) {
				int w = std::max(1, other.width >> level);
				int h = std::max(1, other.height >> level);

				glCopyImageSubData(
					other.id, GL_TEXTURE_2D, level, 0, 0, 0, // src: texture, mip level, x, y, z
					id, GL_TEXTURE_2D, level, 0, 0, 0, // dst: texture, mip level, x, y, z
					w, h, 1 // width, height, depth
				);
			}

			setWrap(other.wrapS, other.wrapT);
			setFilter(other.minFilter, other.magFilter);
			setBorderColor(other.borderColor);
		}

		bool Texture2D::generateMipmaps() {
			// Error check
			if (id == 0)
				return false; // Fail

			glGenerateTextureMipmap(id);
			if (width > 0 && height > 0) {
				mipmaps = 1 + static_cast<unsigned int>(std::floor(std::log2(std::max(width, height))));
			}
			else {
				mipmaps = 1;
			}
			// Success
			return true;
		}

		void Texture2D::bindToSlot(int slotNumber) const {
			glBindTextureUnit(slotNumber, id);
		}
	}
}
