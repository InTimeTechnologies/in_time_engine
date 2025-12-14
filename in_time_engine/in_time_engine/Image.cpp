#include "Image.h"

// Dependencies | std
#include <fstream>

// Dependencies | stb
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

namespace it {
	// class GrayImage

	// Object | public

	// Constructor / Destructor
	GrayImage::GrayImage() : Resource() {

	}
	GrayImage::GrayImage(const std::filesystem::path& path) : Resource() {
		load(path);
	}
	GrayImage::GrayImage(const GrayImage& other) {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return;

		size_t otherDataSize = other.getDataSize();
		data = reinterpret_cast<unsigned char*>(std::malloc(otherDataSize));
		if (data == nullptr)
			return;

		width = other.width;
		height = other.height;
		std::copy(other.data, other.data + otherDataSize, data);
	}
	GrayImage::GrayImage(const GrayAlphaImage& other, bool factorInAlpha) {
		copy(other, factorInAlpha);
	}
	GrayImage::GrayImage(const RGBImage& other) {
		copy(other);
	}
	GrayImage::GrayImage(const RGBAImage& other, bool factorInAlpha) {
		copy(other, factorInAlpha);
	}
	GrayImage::GrayImage(GrayImage&& other) noexcept {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return;

		width = other.width;
		height = other.height;
		data = other.data;

		other.width = 0;
		other.height = 0;
		other.data = nullptr;
	}
	GrayImage::~GrayImage() {
		unload();
	}

	// Operators | assignment
	GrayImage& GrayImage::operator=(const GrayImage& other) {
		copy(other);
		return *this;
	}
	GrayImage& GrayImage::operator=(GrayImage&& other) noexcept {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return *this;

		width = other.width;
		height = other.height;
		data = other.data;

		size_t pixelCount = other.getPixelCount();
		glm::u8vec2* otherData = reinterpret_cast<glm::u8vec2*>(other.data);
		for (size_t i = 0ULL; i < pixelCount; i++) {
			data[i] = otherData[i][0];
		}

		other.width = 0;
		other.height = 0;
		other.data = nullptr;

		return *this;
	}
	GrayImage& GrayImage::operator=(const GrayAlphaImage& other) {
		copy(other, true);
		return *this;
	}
	GrayImage& GrayImage::operator=(GrayAlphaImage&& other) noexcept {
		copy(other, true);
		other.unload();
		return *this;
	}
	GrayImage& GrayImage::operator=(const RGBImage& other) {
		copy(other);
		return *this;
	}
	GrayImage& GrayImage::operator=(RGBImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}
	GrayImage& GrayImage::operator=(const RGBAImage& other) {
		copy(other, true);
		return *this;
	}
	GrayImage& GrayImage::operator=(RGBAImage&& other) noexcept {
		copy(other, true);
		other.unload();
		return *this;
	}


	// Getters
	const std::type_info& GrayImage::getTypeInfo() const {
		return typeid(GrayImage);
	}
	int GrayImage::getWidth() const {
		return width;
	}
	int GrayImage::getHeight() const {
		return height;
	}
	int GrayImage::getChannels() const {
		return CHANNELS;
	}
	unsigned char* GrayImage::getData() const {
		return data;
	}
	size_t GrayImage::getPixelCount() const {
		return static_cast<size_t>(width) * static_cast<size_t>(height);
	}
	size_t GrayImage::getDataSize() const {
		return static_cast<size_t>(width) * static_cast<size_t>(height) * CHANNELS;
	}
	unsigned char GrayImage::getPixel(int x, int y) const {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return 0U;

		// Get pixel
		size_t index = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x));
		return data[index];
	}
	bool GrayImage::isLoaded() const {
		return data != nullptr;
	}

	// Setters
	bool GrayImage::setPixel(int x, int y, unsigned char pixel) {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return false;

		// Set pixel
		size_t index = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x));
		data[index] = pixel;

		// Success
		return true;
	}
	bool GrayImage::setPixel(int x, int y, float pixel) {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return false;

		// Set pixel
		size_t index = static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x);
		data[index] = static_cast<unsigned char>(std::clamp(pixel, 0.0f, 1.0f) * 255.0f);

		// Success
		return true;
	}

	// Functions
	bool GrayImage::load(const std::filesystem::path& path, bool flipImageOnLoad) {
		this->path = path;

		if (path.empty())
			return false; // No path set

		// Free previous data if any
		unload();

		// Read file into memory
		std::ifstream ifstream{ path, std::ios::binary };
		if (!ifstream.is_open())
			return false; // Failed to open file

		ifstream.seekg(0, std::ios::end);
		size_t fileSize{ static_cast<size_t>(ifstream.tellg()) };
		ifstream.seekg(0, std::ios::beg);

		unsigned char* fileData{ static_cast<unsigned char*>(std::malloc(fileSize)) };
		if (fileData == nullptr)
			return false; // Memory allocation failed

		if (!ifstream.read(reinterpret_cast<char*>(fileData), fileSize)) {
			std::free(fileData);
			return false; // Failed to read file
		}
		ifstream.close();

		// Load image from memory
		bool success{ loadFromMemory(fileData, fileSize, flipImageOnLoad) };

		// Free temporary memory
		std::free(fileData);

		return success;
	}
	bool GrayImage::loadFromMemory(const unsigned char* fileInMemory, size_t size, bool flipImageOnLoad) {
		// Error check
		if (fileInMemory == nullptr || size == 0)
			return false;

		// Free previous data if any
		unload();

		// Set vertical flip
		stbi_set_flip_vertically_on_load(flipImageOnLoad);

		// Load image with one channel
		int unusedChannelParameter{ 0 }; // Reason: CHANNELS returns 1, enforcing it to always be 1 channel
		data = stbi_load_from_memory(fileInMemory, static_cast<int>(size), &width, &height, &unusedChannelParameter, CHANNELS);

		return data != nullptr;
	}
	void GrayImage::unload() {
		width = 0;
		height = 0;
		if (data != nullptr) {
			stbi_image_free(data);
			data = nullptr;
		}
	}
	bool GrayImage::copy(const GrayImage& other) {
		// Error check
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t dataSize = other.getDataSize();
		data = reinterpret_cast<unsigned char*>(std::malloc(dataSize));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		std::memcpy(data, other.data, dataSize);

		// Success
		return true;
	}
	bool GrayImage::copy(const GrayAlphaImage& other, bool factorInAlpha) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t otherPixelCount = other.getPixelCount();
		data = reinterpret_cast<unsigned char*>(std::malloc(otherPixelCount));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0; i < otherPixelCount; i++) {
			unsigned char pixel = other.data[i].r;
			if (factorInAlpha) {
				float alphaFactor = other.data[i][1] / 255.0f; // assuming second channel is alpha
				pixel = static_cast<unsigned char>(pixel * alphaFactor);
			}
			data[i] = pixel;
		}

		// Success
		return true;
	}
	bool GrayImage::copy(const RGBImage& other) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t otherPixelCount = other.getPixelCount();
		data = reinterpret_cast<unsigned char*>(std::malloc(otherPixelCount));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < otherPixelCount; i++) {
			unsigned char r = other.data[i].r;
			unsigned char g = other.data[i].g;
			unsigned char b = other.data[i].b;

			// Luminance formula
			unsigned char pixel = static_cast<unsigned char>(
				0.299f * r + 0.587f * g + 0.114f * b
				);

			data[i] = pixel;
		}

		// Success
		return true;
	}
	bool GrayImage::copy(const RGBAImage& other, bool factorInAlpha) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t otherPixelCount = other.getPixelCount();
		data = reinterpret_cast<unsigned char*>(std::malloc(otherPixelCount));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < otherPixelCount; i++) {
			unsigned char r = other.data[i].r;
			unsigned char g = other.data[i].g;
			unsigned char b = other.data[i].b;
			unsigned char a = other.data[i].a;

			// Convert RGBImage to grayscale
			float pixel = 0.299f * r + 0.587f * g + 0.114f * b;

			// Factor in alpha if requested
			if (factorInAlpha) {
				float alphaFactor = a / 255.0f;
				pixel *= alphaFactor;
			}

			data[i] = static_cast<unsigned char>(pixel);
		}

		// Success
		return true;
	}
	bool GrayImage::saveAsPNG(const std::filesystem::path& path) const  {
		const int STRIDE = width * CHANNELS;
		return static_cast<bool>(stbi_write_png(path.string().c_str(), width, height, CHANNELS, data, STRIDE));
	}
	bool GrayImage::saveAsJPEG(const std::filesystem::path& path, int quality) const  {
		return static_cast<bool>(stbi_write_jpg(path.string().c_str(), width, height, CHANNELS, data, quality));
	}
	bool GrayImage::saveAsBMP(const std::filesystem::path& path) const  {
		return static_cast<bool>(stbi_write_bmp(path.string().c_str(), width, height, CHANNELS, data));
	}
	bool GrayImage::saveAsTGA(const std::filesystem::path& path) const  {
		return static_cast<bool>(stbi_write_tga(path.string().c_str(), width, height, CHANNELS, data));
	}
	bool GrayImage::save(const std::filesystem::path& path, int quality) const {
		auto ext = path.extension().string();
		std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

		if (ext == ".png") {
			return saveAsPNG(path);
		}
		else if (ext == ".jpg" || ext == ".jpeg") {
			return saveAsJPEG(path, quality);
		}
		else if (ext == ".bmp") {
			return saveAsBMP(path);
		}
		else if (ext == ".tga") {
			return saveAsTGA(path);
		}

		// Unsupported extension
		return false;
	}

	// class GrayAlphaImage

	// Object | public

	// Constructor / Destructor
	GrayAlphaImage::GrayAlphaImage() : Resource() {

	}
	GrayAlphaImage::GrayAlphaImage(const std::filesystem::path& path) : Resource() {
		load(path);
	}
	GrayAlphaImage::GrayAlphaImage(const GrayImage& other) {
		copy(other);
	}
	GrayAlphaImage::GrayAlphaImage(const GrayAlphaImage& other) {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return;

		size_t otherDataSize = other.getDataSize();
		data = reinterpret_cast<glm::u8vec2*>(std::malloc(otherDataSize));
		if (data == nullptr)
			return;

		width = other.width;
		height = other.height;
		std::copy(other.data, other.data + otherDataSize, data);
	}
	GrayAlphaImage::GrayAlphaImage(const RGBImage& other) {
		copy(other);
	}
	GrayAlphaImage::GrayAlphaImage(const RGBAImage& other) {
		copy(other);
	}
	GrayAlphaImage::GrayAlphaImage(GrayAlphaImage&& other) noexcept {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return;

		width = other.width;
		height = other.height;
		data = other.data;

		other.width = 0;
		other.height = 0;
		other.data = nullptr;
	}
	GrayAlphaImage::~GrayAlphaImage() {
		unload();
	}

	// Operators | assignment
	GrayAlphaImage& GrayAlphaImage::operator=(const GrayImage& other) {
		copy(other);
		return *this;
	}
	GrayAlphaImage& GrayAlphaImage::operator=(GrayImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}
	GrayAlphaImage& GrayAlphaImage::operator=(const GrayAlphaImage& other) {
		copy(other);
		return *this;
	}
	GrayAlphaImage& GrayAlphaImage::operator=(GrayAlphaImage&& other) noexcept {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return *this;

		width = other.width;
		height = other.height;
		data = other.data;

		other.width = 0;
		other.height = 0;
		other.data = nullptr;

		return *this;
	}
	GrayAlphaImage& GrayAlphaImage::operator=(const RGBImage& other) {
		copy(other);
		return *this;
	}
	GrayAlphaImage& GrayAlphaImage::operator=(RGBImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}
	GrayAlphaImage& GrayAlphaImage::operator=(const RGBAImage& other) {
		copy(other);
		return *this;
	}
	GrayAlphaImage& GrayAlphaImage::operator=(RGBAImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}

	// Getters
	const std::type_info& GrayAlphaImage::getTypeInfo() const {
		return typeid(GrayAlphaImage);
	}
	int GrayAlphaImage::getWidth() const {
		return width;
	}
	int GrayAlphaImage::getHeight() const {
		return height;
	}
	int GrayAlphaImage::getChannels() const {
		return CHANNELS;
	}
	glm::u8vec2* GrayAlphaImage::getData() const {
		return data;
	}
	size_t GrayAlphaImage::getPixelCount() const {
		return static_cast<size_t>(width) * static_cast<size_t>(height);
	}
	size_t GrayAlphaImage::getDataSize() const {
		return static_cast<size_t>(width) * static_cast<size_t>(height) * CHANNELS;
	}
	glm::u8vec2 GrayAlphaImage::getPixel(int x, int y) const {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return glm::u8vec2(0);

		// Get pixel
		size_t index = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x));
		return reinterpret_cast<glm::u8vec2*>(data)[index];
	}
	bool GrayAlphaImage::isLoaded() const {
		return data != nullptr;
	}

	// Setters
	bool GrayAlphaImage::setPixel(int x, int y, glm::u8vec2 pixel) {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return false;

		// Set pixel
		size_t index = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x));
		reinterpret_cast<glm::u8vec2*>(data)[index] = pixel;

		// Success
		return true;
	}
	bool GrayAlphaImage::setPixel(int x, int y, glm::vec2 pixel) {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return false;

		// Set pixel
		size_t index = static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x);
		reinterpret_cast<glm::u8vec2*>(data)[index] = glm::u8vec2(
			static_cast<unsigned char>(std::clamp(pixel[0], 0.0f, 1.0f) * 255.0f),
			static_cast<unsigned char>(std::clamp(pixel[1], 0.0f, 1.0f) * 255.0f)
		);

		// Success
		return true;
	}

	// Functions
	bool GrayAlphaImage::load(const std::filesystem::path& path, bool flipImageOnLoad) {
		this->path = path;

		if (path.empty())
			return false; // No path set

		// Free previous data if any
		unload();

		// Read file into memory
		std::ifstream ifstream{ path, std::ios::binary };
		if (!ifstream.is_open())
			return false; // Failed to open file

		ifstream.seekg(0, std::ios::end);
		size_t fileSize{ static_cast<size_t>(ifstream.tellg()) };
		ifstream.seekg(0, std::ios::beg);

		unsigned char* fileData{ static_cast<unsigned char*>(std::malloc(fileSize)) };
		if (fileData == nullptr)
			return false; // Memory allocation failed

		if (!ifstream.read(reinterpret_cast<char*>(fileData), fileSize)) {
			std::free(fileData);
			return false; // Failed to read file
		}
		ifstream.close();

		// Load image from memory
		bool success{ loadFromMemory(fileData, fileSize, flipImageOnLoad) };

		// Free temporary memory
		std::free(fileData);

		return success;
	}
	bool GrayAlphaImage::loadFromMemory(const unsigned char* fileInMemory, size_t size, bool flipImageOnLoad) {
		// Error check
		if (fileInMemory == nullptr || size == 0)
			return false;

		// Free previous data if any
		unload();

		// Set vertical flip
		stbi_set_flip_vertically_on_load(flipImageOnLoad);

		// Load image with one channel
		int unusedChannelParameter{ 0 }; // Reason: CHANNELS returns 2, enforcing it to always be 2 channel
		data = reinterpret_cast<glm::u8vec2*>(stbi_load_from_memory(fileInMemory, static_cast<int>(size), &width, &height, &unusedChannelParameter, CHANNELS));

		return data != nullptr;
	}
	void GrayAlphaImage::unload() {
		width = 0;
		height = 0;
		if (data != nullptr) {
			stbi_image_free(data);
			data = nullptr;
		}
	}
	bool GrayAlphaImage::copy(const GrayImage& other) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec2*>(std::malloc(pixelCount * sizeof(glm::u8vec2)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++)
			data[i] = glm::u8vec2(other.data[i], 255U);

		// Success
		return true;
	}
	bool GrayAlphaImage::copy(const GrayAlphaImage& other) {
		// Error check
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t dataSize = other.getDataSize();
		data = reinterpret_cast<glm::u8vec2*>(std::malloc(dataSize));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		std::memcpy(data, other.data, dataSize);

		// Success
		return true;
	}
	bool GrayAlphaImage::copy(const RGBImage& other) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec2*>(std::malloc(pixelCount * sizeof(glm::u8vec2)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++) {
			unsigned char r = other.data[i].r;
			unsigned char g = other.data[i].g;
			unsigned char b = other.data[i].b;

			// Luminance formula
			unsigned char grayValue = static_cast<unsigned char>(
				0.299f * r + 0.587f * g + 0.114f * b
				);

			data[i] = glm::u8vec2(grayValue, 255U);
		}

		// Success
		return true;
	}
	bool GrayAlphaImage::copy(const RGBAImage& other) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec2*>(std::malloc(pixelCount * sizeof(glm::u8vec2)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++) {
			unsigned char r = other.data[i].r;
			unsigned char g = other.data[i].g;
			unsigned char b = other.data[i].b;

			// Luminance formula
			unsigned char grayValue = static_cast<unsigned char>(
				0.299f * r + 0.587f * g + 0.114f * b
				);

			data[i] = glm::u8vec2(grayValue, other.data[i].a);
		}

		// Success
		return true;
	}
	bool GrayAlphaImage::saveAsPNG(const std::filesystem::path& path) const {
		const int STRIDE = width * CHANNELS;
		return static_cast<bool>(stbi_write_png(path.string().c_str(), width, height, CHANNELS, data, STRIDE));
	}
	bool GrayAlphaImage::saveAsJPEG(const std::filesystem::path& path, int quality) const {
		return static_cast<bool>(stbi_write_jpg(path.string().c_str(), width, height, CHANNELS, data, quality));
	}
	bool GrayAlphaImage::saveAsBMP(const std::filesystem::path& path) const {
		return static_cast<bool>(stbi_write_bmp(path.string().c_str(), width, height, CHANNELS, data));
	}
	bool GrayAlphaImage::saveAsTGA(const std::filesystem::path& path) const {
		return static_cast<bool>(stbi_write_tga(path.string().c_str(), width, height, CHANNELS, data));
	}
	bool GrayAlphaImage::save(const std::filesystem::path& path, int quality) const {
		auto ext = path.extension().string();
		std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

		if (ext == ".png") {
			return saveAsPNG(path);
		}
		else if (ext == ".jpg" || ext == ".jpeg") {
			return saveAsJPEG(path, quality);
		}
		else if (ext == ".bmp") {
			return saveAsBMP(path);
		}
		else if (ext == ".tga") {
			return saveAsTGA(path);
		}

		// Unsupported extension
		return false;
	}

	// class RGBImage

	// Object | public

	// Constructor / Destructor
	RGBImage::RGBImage() : Resource() {

	}
	RGBImage::RGBImage(const std::filesystem::path& path) : Resource() {
		load(path);
	}
	RGBImage::RGBImage(const GrayImage& other) {
		copy(other);
	}
	RGBImage::RGBImage(const GrayAlphaImage& other, bool factorInAlpha) {
		copy(other, factorInAlpha);
	}
	RGBImage::RGBImage(const RGBImage& other) {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return;

		size_t otherDataSize = other.getDataSize();
		data = reinterpret_cast<glm::u8vec3*>(std::malloc(otherDataSize));
		if (data == nullptr)
			return;

		width = other.width;
		height = other.height;
		std::copy(other.data, other.data + otherDataSize, data);
	}
	RGBImage::RGBImage(const RGBAImage& other, bool factorInAlpha) {
		copy(other, factorInAlpha);
	}
	RGBImage::RGBImage(RGBImage&& other) noexcept {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return;

		width = other.width;
		height = other.height;
		data = other.data;

		other.width = 0;
		other.height = 0;
		other.data = nullptr;
	}
	RGBImage::~RGBImage() {
		unload();
	}

	// Operators | assignment
	RGBImage& RGBImage::operator=(const GrayImage& other) {
		copy(other);
		return *this;
	}
	RGBImage& RGBImage::operator=(GrayImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}
	RGBImage& RGBImage::operator=(const GrayAlphaImage& other) {
		copy(other);
		return *this;
	}
	RGBImage& RGBImage::operator=(GrayAlphaImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}
	RGBImage& RGBImage::operator=(const RGBImage& other) {
		copy(other);
		return *this;
	}
	RGBImage& RGBImage::operator=(RGBImage&& other) noexcept {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return *this;

		width = other.width;
		height = other.height;
		data = other.data;

		other.width = 0;
		other.height = 0;
		other.data = nullptr;

		return *this;
	}
	RGBImage& RGBImage::operator=(const RGBAImage& other) {
		copy(other);
		return *this;
	}
	RGBImage& RGBImage::operator=(RGBAImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}

	// Getters
	const std::type_info& RGBImage::getTypeInfo() const {
		return typeid(RGBImage);
	}
	int RGBImage::getWidth() const {
		return width;
	}
	int RGBImage::getHeight() const {
		return height;
	}
	int RGBImage::getChannels() const {
		return CHANNELS;
	}
	glm::u8vec3* RGBImage::getData() const {
		return data;
	}
	size_t RGBImage::getPixelCount() const {
		return static_cast<size_t>(width) * static_cast<size_t>(height);
	}
	size_t RGBImage::getDataSize() const {
		return static_cast<size_t>(width) * static_cast<size_t>(height) * CHANNELS;
	}
	glm::u8vec3 RGBImage::getPixel(int x, int y) const {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return glm::u8vec3(0);

		// Get pixel
		size_t index = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x));
		return reinterpret_cast<glm::u8vec3*>(data)[index];
	}
	bool RGBImage::isLoaded() const {
		return data != nullptr;
	}

	// Setters
	bool RGBImage::setPixel(int x, int y, glm::u8vec3 pixel) {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return false;

		// Set pixel
		size_t index = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x));
		reinterpret_cast<glm::u8vec3*>(data)[index] = pixel;

		// Success
		return true;
	}
	bool RGBImage::setPixel(int x, int y, glm::vec3 pixel) {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return false;

		// Set pixel
		size_t index = static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x);
		reinterpret_cast<glm::u8vec3*>(data)[index] = glm::u8vec3(
			static_cast<unsigned char>(std::clamp(pixel[0], 0.0f, 1.0f) * 255.0f),
			static_cast<unsigned char>(std::clamp(pixel[1], 0.0f, 1.0f) * 255.0f),
			static_cast<unsigned char>(std::clamp(pixel[2], 0.0f, 1.0f) * 255.0f)
		);

		// Success
		return true;
	}

	// Functions
	bool RGBImage::load(const std::filesystem::path& path, bool flipImageOnLoad) {
		this->path = path;

		if (path.empty())
			return false; // No path set

		// Free previous data if any
		unload();

		// Read file into memory
		std::ifstream ifstream{ path, std::ios::binary };
		if (!ifstream.is_open())
			return false; // Failed to open file

		ifstream.seekg(0, std::ios::end);
		size_t fileSize{ static_cast<size_t>(ifstream.tellg()) };
		ifstream.seekg(0, std::ios::beg);

		unsigned char* fileData{ static_cast<unsigned char*>(std::malloc(fileSize)) };
		if (fileData == nullptr)
			return false; // Memory allocation failed

		if (!ifstream.read(reinterpret_cast<char*>(fileData), fileSize)) {
			std::free(fileData);
			return false; // Failed to read file
		}
		ifstream.close();

		// Load image from memory
		bool success{ loadFromMemory(fileData, fileSize, flipImageOnLoad) };

		// Free temporary memory
		std::free(fileData);

		return success;
	}
	bool RGBImage::loadFromMemory(const unsigned char* fileInMemory, size_t size, bool flipImageOnLoad) {
		// Error check
		if (fileInMemory == nullptr || size == 0)
			return false;

		// Free previous data if any
		unload();

		// Set vertical flip
		stbi_set_flip_vertically_on_load(flipImageOnLoad);

		// Load image with one channel
		int unusedChannelParameter{ 0 }; // Reason: CHANNELS returns 3, enforcing it to always be 3 channel
		data = reinterpret_cast<glm::u8vec3*>(stbi_load_from_memory(fileInMemory, static_cast<int>(size), &width, &height, &unusedChannelParameter, CHANNELS));

		return data != nullptr;
	}
	void RGBImage::unload() {
		width = 0;
		height = 0;
		if (data != nullptr) {
			stbi_image_free(data);
			data = nullptr;
		}
	}
	bool RGBImage::copy(const GrayImage& other) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec3*>(std::malloc(pixelCount * sizeof(glm::u8vec3)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++)
			data[i] = glm::u8vec3(other.data[i], other.data[i], other.data[i]);

		// Success
		return true;
	}
	bool RGBImage::copy(const GrayAlphaImage& other, bool factorInAlpha) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec3*>(std::malloc(pixelCount * sizeof(glm::u8vec3)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++) {
			unsigned char gray = other.data[i].x;   // grayscale value
			unsigned char alpha = other.data[i].y;  // alpha value

			if (factorInAlpha) {
				// Scale grayscale by alpha (normalized to 0–255)
				unsigned char scaled = static_cast<unsigned char>((gray * alpha) / 255);
				data[i] = glm::u8vec3(scaled, scaled, scaled);
			}
			else {
				// Just copy grayscale into RGBImage
				data[i] = glm::u8vec3(gray, gray, gray);
			}
		}

		// Success
		return true;
	}
	bool RGBImage::copy(const RGBImage& other) {
		// Error check
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t dataSize = other.getDataSize();
		data = reinterpret_cast<glm::u8vec3*>(std::malloc(dataSize));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		std::memcpy(data, other.data, dataSize);

		// Success
		return true;
	}
	bool RGBImage::copy(const RGBAImage& other, bool factorInAlpha) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec3*>(std::malloc(pixelCount * sizeof(glm::u8vec3)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++) {
			unsigned char r = other.data[i].r;
			unsigned char g = other.data[i].g;
			unsigned char b = other.data[i].b;
			unsigned char a = other.data[i].a;

			if (factorInAlpha) {
				// Premultiply by alpha
				r = static_cast<unsigned char>((r * a) / 255);
				g = static_cast<unsigned char>((g * a) / 255);
				b = static_cast<unsigned char>((b * a) / 255);
			}

			data[i] = glm::u8vec3(r, g, b);
		}
		// Success
		return true;
	}
	bool RGBImage::saveAsPNG(const std::filesystem::path& path) const {
		const int STRIDE = width * CHANNELS;
		return static_cast<bool>(stbi_write_png(path.string().c_str(), width, height, CHANNELS, data, STRIDE));
	}
	bool RGBImage::saveAsJPEG(const std::filesystem::path& path, int quality) const {
		return static_cast<bool>(stbi_write_jpg(path.string().c_str(), width, height, CHANNELS, data, quality));
	}
	bool RGBImage::saveAsBMP(const std::filesystem::path& path) const {
		return static_cast<bool>(stbi_write_bmp(path.string().c_str(), width, height, CHANNELS, data));
	}
	bool RGBImage::saveAsTGA(const std::filesystem::path& path) const {
		return static_cast<bool>(stbi_write_tga(path.string().c_str(), width, height, CHANNELS, data));
	}
	bool RGBImage::save(const std::filesystem::path& path, int quality) const {
		auto ext = path.extension().string();
		std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

		if (ext == ".png") {
			return saveAsPNG(path);
		}
		else if (ext == ".jpg" || ext == ".jpeg") {
			return saveAsJPEG(path, quality);
		}
		else if (ext == ".bmp") {
			return saveAsBMP(path);
		}
		else if (ext == ".tga") {
			return saveAsTGA(path);
		}

		// Unsupported extension
		return false;
	}

	// class RGBAImage

	// Object | public

	// Constructor / Destructor
	RGBAImage::RGBAImage() : Resource() {

	}
	RGBAImage::RGBAImage(const std::filesystem::path& path) : Resource() {
		load(path);
	}
	RGBAImage::RGBAImage(const GrayImage& other) {
		copy(other);
	}
	RGBAImage::RGBAImage(const GrayAlphaImage& other) {
		copy(other);
	}
	RGBAImage::RGBAImage(const RGBImage& other) {
		copy(other);
	}
	RGBAImage::RGBAImage(const RGBAImage& other) {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return;

		size_t otherDataSize = other.getDataSize();
		data = reinterpret_cast<glm::u8vec4*>(std::malloc(otherDataSize));
		if (data == nullptr)
			return;

		width = other.width;
		height = other.height;
		std::copy(other.data, other.data + otherDataSize, data);
	}
	RGBAImage::RGBAImage(RGBAImage&& other) noexcept {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return;

		width = other.width;
		height = other.height;
		data = other.data;

		other.width = 0;
		other.height = 0;
		other.data = nullptr;
	}
	RGBAImage::~RGBAImage() {
		unload();
	}

	// Operators | assignment
	RGBAImage& RGBAImage::operator=(const GrayImage& other) {
		copy(other);
		return *this;
	}
	RGBAImage& RGBAImage::operator=(GrayImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}
	RGBAImage& RGBAImage::operator=(const GrayAlphaImage& other) {
		copy(other);
		return *this;
	}
	RGBAImage& RGBAImage::operator=(GrayAlphaImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}
	RGBAImage& RGBAImage::operator=(const RGBImage& other) {
		copy(other);
		return *this;
	}
	RGBAImage& RGBAImage::operator=(RGBImage&& other) noexcept {
		copy(other);
		other.unload();
		return *this;
	}
	RGBAImage& RGBAImage::operator=(const RGBAImage& other) {
		copy(other);
		return *this;
	}
	RGBAImage& RGBAImage::operator=(RGBAImage&& other) noexcept {
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return *this;

		width = other.width;
		height = other.height;
		data = other.data;

		other.width = 0;
		other.height = 0;
		other.data = nullptr;

		return *this;
	}

	// Getters
	const std::type_info& RGBAImage::getTypeInfo() const {
		return typeid(RGBAImage);
	}
	int RGBAImage::getWidth() const {
		return width;
	}
	int RGBAImage::getHeight() const {
		return height;
	}
	int RGBAImage::getChannels() const {
		return CHANNELS;
	}
	glm::u8vec4* RGBAImage::getData() const {
		return data;
	}
	size_t RGBAImage::getPixelCount() const {
		return static_cast<size_t>(width) * static_cast<size_t>(height);
	}
	size_t RGBAImage::getDataSize() const {
		return static_cast<size_t>(width) * static_cast<size_t>(height) * CHANNELS;
	}
	glm::u8vec4 RGBAImage::getPixel(int x, int y) const {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return glm::u8vec4(0);

		// Get pixel
		size_t index = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x));
		return reinterpret_cast<glm::u8vec4*>(data)[index];
	}
	bool RGBAImage::isLoaded() const {
		return data != nullptr;
	}

	// Setters
	bool RGBAImage::setPixel(int x, int y, glm::u8vec4 pixel) {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return false;

		// Set pixel
		size_t index = (static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x));
		reinterpret_cast<glm::u8vec4*>(data)[index] = pixel;

		// Success
		return true;
	}
	bool RGBAImage::setPixel(int x, int y, glm::vec4 pixel) {
		// Error check
		if (!data || x < 0 || x >= width || y < 0 || y >= height)
			return false;

		// Set pixel
		size_t index = static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x);
		reinterpret_cast<glm::u8vec4*>(data)[index] = glm::u8vec4(
			static_cast<unsigned char>(std::clamp(pixel[0], 0.0f, 1.0f) * 255.0f),
			static_cast<unsigned char>(std::clamp(pixel[1], 0.0f, 1.0f) * 255.0f),
			static_cast<unsigned char>(std::clamp(pixel[2], 0.0f, 1.0f) * 255.0f),
			static_cast<unsigned char>(std::clamp(pixel[3], 0.0f, 1.0f) * 255.0f)
		);

		// Success
		return true;
	}

	// Functions
	bool RGBAImage::load(const std::filesystem::path& path, bool flipImageOnLoad) {
		this->path = path;

		if (path.empty())
			return false; // No path set

		// Free previous data if any
		unload();

		// Read file into memory
		std::ifstream ifstream{ path, std::ios::binary };
		if (!ifstream.is_open())
			return false; // Failed to open file

		ifstream.seekg(0, std::ios::end);
		size_t fileSize{ static_cast<size_t>(ifstream.tellg()) };
		ifstream.seekg(0, std::ios::beg);

		unsigned char* fileData{ static_cast<unsigned char*>(std::malloc(fileSize)) };
		if (fileData == nullptr)
			return false; // Memory allocation failed

		if (!ifstream.read(reinterpret_cast<char*>(fileData), fileSize)) {
			std::free(fileData);
			return false; // Failed to read file
		}
		ifstream.close();

		// Load image from memory
		bool success{ loadFromMemory(fileData, fileSize, flipImageOnLoad) };

		// Free temporary memory
		std::free(fileData);

		return success;
	}
	bool RGBAImage::loadFromMemory(const unsigned char* fileInMemory, size_t size, bool flipImageOnLoad) {
		// Error check
		if (fileInMemory == nullptr || size == 0)
			return false;

		// Free previous data if any
		unload();

		// Set vertical flip
		stbi_set_flip_vertically_on_load(flipImageOnLoad);

		// Load image with one channel
		int unusedChannelParameter{ 0 }; // Reason: CHANNELS returns 4, enforcing it to always be 4 channel
		data = reinterpret_cast<glm::u8vec4*>(stbi_load_from_memory(fileInMemory, static_cast<int>(size), &width, &height, &unusedChannelParameter, CHANNELS));

		return data != nullptr;
	}
	void RGBAImage::unload() {
		width = 0;
		height = 0;
		if (data != nullptr) {
			stbi_image_free(data);
			data = nullptr;
		}
	}
	bool RGBAImage::copy(const GrayImage& other) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec4*>(std::malloc(pixelCount * sizeof(glm::u8vec4)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++)
			data[i] = glm::u8vec4(other.data[i], other.data[i], other.data[i], 255U);

		// Success
		return true;
	}
	bool RGBAImage::copy(const GrayAlphaImage& other) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec4*>(std::malloc(pixelCount * sizeof(glm::u8vec4)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++)
			data[i] = glm::u8vec4(other.data[i][0], other.data[i][0], other.data[i][0], other.data[i][1]);

		// Success
		return true;
	}
	bool RGBAImage::copy(const RGBImage& other) {
		// Error check
		if (other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t pixelCount = other.getPixelCount();
		data = reinterpret_cast<glm::u8vec4*>(std::malloc(pixelCount * sizeof(glm::u8vec4)));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		for (size_t i = 0ULL; i < pixelCount; i++)
			data[i] = glm::u8vec4(other.data[i].r, other.data[i].g, other.data[i].b, 255U);

		// Success
		return true;
	}
	bool RGBAImage::copy(const RGBAImage& other) {
		// Error check
		if (this == &other || other.width <= 0 || other.height <= 0 || other.data == nullptr)
			return false;

		// Release existing data
		unload();

		// Allocate memory for copy operation
		size_t dataSize = other.getDataSize();
		data = reinterpret_cast<glm::u8vec4*>(std::malloc(dataSize));
		if (data == nullptr)
			return false;
		width = other.width;
		height = other.height;

		// Copy data
		std::memcpy(data, other.data, dataSize);

		// Success
		return true;
	}
	bool RGBAImage::saveAsPNG(const std::filesystem::path& path) const {
		const int STRIDE = width * CHANNELS;
		return static_cast<bool>(stbi_write_png(path.string().c_str(), width, height, CHANNELS, data, STRIDE));
	}
	bool RGBAImage::saveAsJPEG(const std::filesystem::path& path, int quality) const {
		return static_cast<bool>(stbi_write_jpg(path.string().c_str(), width, height, CHANNELS, data, quality));
	}
	bool RGBAImage::saveAsBMP(const std::filesystem::path& path) const {
		return static_cast<bool>(stbi_write_bmp(path.string().c_str(), width, height, CHANNELS, data));
	}
	bool RGBAImage::saveAsTGA(const std::filesystem::path& path) const {
		return static_cast<bool>(stbi_write_tga(path.string().c_str(), width, height, CHANNELS, data));
	}
	bool RGBAImage::save(const std::filesystem::path& path, int quality) const {
		auto ext = path.extension().string();
		std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

		if (ext == ".png") {
			return saveAsPNG(path);
		}
		else if (ext == ".jpg" || ext == ".jpeg") {
			return saveAsJPEG(path, quality);
		}
		else if (ext == ".bmp") {
			return saveAsBMP(path);
		}
		else if (ext == ".tga") {
			return saveAsTGA(path);
		}

		// Unsupported extension
		return false;
	}
}
