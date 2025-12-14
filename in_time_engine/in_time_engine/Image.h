#pragma once

// Dependencies | std
#include <filesystem>

// Dependencies | glm
#include <glm/glm.hpp>

// Dependencies | in_time_engine
#include "Resource.h"

namespace it {
	// Forward declarations
	class GrayImage;
	class GrayAlphaImage;
	class RGBImage;
	class RGBAImage;

	// Enums
	enum class DynamicRange {
		UNKNOWN = -1,
		LDR,
		HDR
	};
	enum class Format {
		UNKNOWN = -1,
		JPEG,
		PNG,
		TGA,
		BMP,
		PSD,
		GIF,
		HDR,
		PIC,
		PNM
	};

	// Classes	
	class GrayImage : public Resource {
		// Friends
		friend class GrayAlphaImage;
		friend class RGBImage;
		friend class RGBAImage;

		// Static
		public:
			// Properties
			static const int CHANNELS{ 1 };

		// Object
		private:
			// Properties
			int width{ 0 };
			int height{ 0 };
			unsigned char* data{ nullptr };

		public:
			// Constructor / Destructor
			GrayImage();
			GrayImage(const std::filesystem::path& path);
			GrayImage(const GrayImage& other);
			GrayImage(const GrayAlphaImage& other, bool factorInAlpha = false);
			GrayImage(const RGBImage& other);
			GrayImage(const RGBAImage& other, bool factorInAlpha = false);
			GrayImage(GrayImage&& other) noexcept;
			~GrayImage();

			// Operators | assignment
			GrayImage& operator=(const GrayImage& other);
			GrayImage& operator=(GrayImage&& other) noexcept;
			GrayImage& operator=(const GrayAlphaImage& other);
			GrayImage& operator=(GrayAlphaImage&& other) noexcept;
			GrayImage& operator=(const RGBImage& other);
			GrayImage& operator=(RGBImage&& other) noexcept;
			GrayImage& operator=(const RGBAImage& other);
			GrayImage& operator=(RGBAImage&& other) noexcept;

			// Getters
			const std::type_info& getTypeInfo() const override;
			int getWidth() const;
			int getHeight() const;
			int getChannels() const;
			unsigned char* getData() const;
			size_t getPixelCount() const;
			size_t getDataSize() const;
			unsigned char getPixel(int x, int y) const;
			bool isLoaded() const;

			// Setters
			bool setPixel(int x, int y, unsigned char pixel);
			bool setPixel(int x, int y, float pixel);

			// Functions
			bool load(const std::filesystem::path& path, bool flipImageOnLoad = false);
			bool loadFromMemory(const unsigned char* fileInMemory, size_t size, bool flipImageOnLoad = false);
			void unload();
			bool copy(const GrayImage& other);
			bool copy(const GrayAlphaImage& other, bool factorInAlpha = false);
			bool copy(const RGBImage& other);
			bool copy(const RGBAImage& other, bool factorInAlpha = false);
			bool saveAsPNG(const std::filesystem::path& path) const;
			bool saveAsJPEG(const std::filesystem::path& path, int quality = 90) const;
			bool saveAsBMP(const std::filesystem::path& path) const;
			bool saveAsTGA(const std::filesystem::path& path) const;
			bool save(const std::filesystem::path& path, int quality = 90) const;
	};
	class GrayAlphaImage : public Resource {
		// Friends
		friend class GrayImage;
		friend class RGBImage;
		friend class RGBAImage;

		// Static
		public:
			// Properties
			static const int CHANNELS{ 2 };

		// Object
		private:
			// Properties
			int width{ 0 };
			int height{ 0 };
			glm::u8vec2* data{ nullptr };

		public:
			// Constructor / Destructor
			GrayAlphaImage();
			GrayAlphaImage(const std::filesystem::path& path);
			GrayAlphaImage(const GrayImage& other);
			GrayAlphaImage(const GrayAlphaImage& other);
			GrayAlphaImage(const RGBImage& other);
			GrayAlphaImage(const RGBAImage& other);
			GrayAlphaImage(GrayAlphaImage&& other) noexcept;
			~GrayAlphaImage();

			// Operators | assignment
			GrayAlphaImage& operator=(const GrayImage& other);
			GrayAlphaImage& operator=(GrayImage&& other) noexcept;
			GrayAlphaImage& operator=(const GrayAlphaImage& other);
			GrayAlphaImage& operator=(GrayAlphaImage&& other) noexcept;
			GrayAlphaImage& operator=(const RGBImage& other);
			GrayAlphaImage& operator=(RGBImage&& other) noexcept;
			GrayAlphaImage& operator=(const RGBAImage& other);
			GrayAlphaImage& operator=(RGBAImage&& other) noexcept;

			// Getters
			const std::type_info& getTypeInfo() const override;
			int getWidth() const;
			int getHeight() const;
			int getChannels() const;
			glm::u8vec2* getData() const;
			size_t getPixelCount() const;
			size_t getDataSize() const;
			glm::u8vec2 getPixel(int x, int y) const;
			bool isLoaded() const;

			// Setters
			bool setPixel(int x, int y, glm::u8vec2 pixel);
			bool setPixel(int x, int y, glm::vec2 pixel);

			// Functions
			bool load(const std::filesystem::path& path, bool flipImageOnLoad = false);
			bool loadFromMemory(const unsigned char* fileInMemory, size_t size, bool flipImageOnLoad = false);
			void unload();
			bool copy(const GrayImage& other);
			bool copy(const GrayAlphaImage& other);
			bool copy(const RGBImage& other);
			bool copy(const RGBAImage& other);
			bool saveAsPNG(const std::filesystem::path& path) const;
			bool saveAsJPEG(const std::filesystem::path& path, int quality = 90) const;
			bool saveAsBMP(const std::filesystem::path& path) const;
			bool saveAsTGA(const std::filesystem::path& path) const;
			bool save(const std::filesystem::path& path, int quality = 90) const;
	};
	class RGBImage : public Resource {
		// Friends
		friend class GrayImage;
		friend class GrayAlphaImage;
		friend class RGBAImage;

		// Static
		public:
			// Properties
			static const int CHANNELS{ 3 };

		// Object
		private:
			// Properties
			int width{ 0 };
			int height{ 0 };
			glm::u8vec3* data{ nullptr };

		public:
			// Constructor / Destructor
			RGBImage();
			RGBImage(const std::filesystem::path& path);
			RGBImage(const GrayImage& other);
			RGBImage(const GrayAlphaImage& other, bool factorInAlpha = false);
			RGBImage(const RGBImage& other);
			RGBImage(const RGBAImage& other, bool factorInAlpha = false);
			RGBImage(RGBImage&& other) noexcept;
			~RGBImage();

			// Operators | assignment
			RGBImage& operator=(const GrayImage& other);
			RGBImage& operator=(GrayImage&& other) noexcept;
			RGBImage& operator=(const GrayAlphaImage& other);
			RGBImage& operator=(GrayAlphaImage&& other) noexcept;
			RGBImage& operator=(const RGBImage& other);
			RGBImage& operator=(RGBImage&& other) noexcept;
			RGBImage& operator=(const RGBAImage& other);
			RGBImage& operator=(RGBAImage&& other) noexcept;

			// Getters
			const std::type_info& getTypeInfo() const override;
			int getWidth() const;
			int getHeight() const;
			int getChannels() const;
			glm::u8vec3* getData() const;
			size_t getPixelCount() const;
			size_t getDataSize() const;
			glm::u8vec3 getPixel(int x, int y) const;
			bool isLoaded() const;

			// Setters
			bool setPixel(int x, int y, glm::u8vec3 pixel);
			bool setPixel(int x, int y, glm::vec3 pixel);

			// Functions
			bool load(const std::filesystem::path& path, bool flipImageOnLoad = false);
			bool loadFromMemory(const unsigned char* fileInMemory, size_t size, bool flipImageOnLoad = false);
			void unload();
			bool copy(const GrayImage& other);
			bool copy(const GrayAlphaImage& other, bool factorInAlpha = false);
			bool copy(const RGBImage& other);
			bool copy(const RGBAImage& other, bool factorInAlpha = false);
			bool saveAsPNG(const std::filesystem::path& path) const;
			bool saveAsJPEG(const std::filesystem::path& path, int quality = 90) const;
			bool saveAsBMP(const std::filesystem::path& path) const;
			bool saveAsTGA(const std::filesystem::path& path) const;
			bool save(const std::filesystem::path& path, int quality = 90) const;
	};
	class RGBAImage : public Resource {
		// Friends
		friend class GrayImage;
		friend class GrayAlphaImage;
		friend class RGBImage;

		// Static
		public:
			// Properties
			static const int CHANNELS{ 4 };

		// Object
		private:
			// Properties
			int width{ 0 };
			int height{ 0 };
			glm::u8vec4* data{ nullptr };

		public:
			// Constructor / Destructor
			RGBAImage();
			RGBAImage(const std::filesystem::path& path);
			RGBAImage(const GrayImage& other);
			RGBAImage(const GrayAlphaImage& other);
			RGBAImage(const RGBImage& other);
			RGBAImage(const RGBAImage& other);
			RGBAImage(RGBAImage&& other) noexcept;
			~RGBAImage();

			// Operators | assignment
			RGBAImage& operator=(const GrayImage& other);
			RGBAImage& operator=(GrayImage&& other) noexcept;
			RGBAImage& operator=(const GrayAlphaImage& other);
			RGBAImage& operator=(GrayAlphaImage&& other) noexcept;
			RGBAImage& operator=(const RGBImage& other);
			RGBAImage& operator=(RGBImage&& other) noexcept;
			RGBAImage& operator=(const RGBAImage& other);
			RGBAImage& operator=(RGBAImage&& other) noexcept;

			// Getters
			const std::type_info& getTypeInfo() const override;
			int getWidth() const;
			int getHeight() const;
			int getChannels() const;
			glm::u8vec4* getData() const;
			size_t getPixelCount() const;
			size_t getDataSize() const;
			glm::u8vec4 getPixel(int x, int y) const;
			bool isLoaded() const;

			// Setters
			bool setPixel(int x, int y, glm::u8vec4 pixel);
			bool setPixel(int x, int y, glm::vec4 pixel);

			// Functions
			bool load(const std::filesystem::path& path, bool flipImageOnLoad = false);
			bool loadFromMemory(const unsigned char* fileInMemory, size_t size, bool flipImageOnLoad = false);
			void unload();
			bool copy(const GrayImage& other);
			bool copy(const GrayAlphaImage& other);
			bool copy(const RGBImage& other);
			bool copy(const RGBAImage& other);
			bool saveAsPNG(const std::filesystem::path& path) const;
			bool saveAsJPEG(const std::filesystem::path& path, int quality = 90) const;
			bool saveAsBMP(const std::filesystem::path& path) const;
			bool saveAsTGA(const std::filesystem::path& path) const;
			bool save(const std::filesystem::path& path, int quality = 90) const;
	};
}
