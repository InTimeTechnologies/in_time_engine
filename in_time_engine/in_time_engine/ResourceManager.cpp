#include "ResourceManager.h"

// Dependencies | in_time_engine
#include "Resource.h"
#include "InTimeEngine.h"

// class it::ResourceManager::KeyHasher

// Object | public

// Operators | ()
std::size_t it::ResourceManager::KeyHasher::operator()(const std::string& key) const {
	std::hash<std::string> hasher;
	return hasher(key);
}

// class it::ResourceManager::KeyComperator

// Object | public

// Operators | ()
bool it::ResourceManager::KeyComperator::operator()(const std::string& leftResourcePath, const std::string& rightResourcePath) const {
	return leftResourcePath == rightResourcePath;
}

// class it::ResourceManager

// Object | public

// Constructor / Destructor
it::ResourceManager::ResourceManager(InTimeEngine* inTimeEngine) : inTimeEngine(inTimeEngine) {

}

// Getters
it::InTimeEngine* it::ResourceManager::getInTimeEngine() const {
	return inTimeEngine;
}

// Functions
bool it::ResourceManager::has(const std::filesystem::path& path) const {
	// Normalize path to string key
	std::string resourcePath{ path.string() };

	// Check if the resource exists in the map
	auto iterator = resources.find(resourcePath);
	if (iterator != resources.end()) {
		// Extra safety: verify the shared_ptr isn’t null
		if (iterator->second != nullptr)
			return true;
	}

	// Resource not found
	return false;
}
std::shared_ptr<it::Resource> it::ResourceManager::get(const std::filesystem::path& path) const {
	// Check if resource exists
	std::string resourcePath = path.string(); 
	auto iterator = resources.find(resourcePath);
	if (iterator != resources.end()) {
		std::shared_ptr<Resource> resource = iterator->second;
		if (resource != nullptr)
			return resource; // Resource found
	}

	// Resource not found. Return empty shared pointer
	return std::shared_ptr<Resource>{};
}

std::shared_ptr<it::Resource> it::ResourceManager::load(const std::filesystem::path& path) {
	// Resource to return
	std::shared_ptr<Resource> resource{};

	// Check if resource already exists
	std::string resourcePath{ path.string() };
	auto iterator{ resources.find(resourcePath) };
	if (iterator != resources.end()) {
		resource = iterator->second;
		if (resource != nullptr)
			return resource;
		return std::shared_ptr<Resource>{};
	}

	// Create resource based on file extension
	std::string extension{ path.extension().string() };
	if (extension == ".png" || extension == ".jpg" || extension == ".jpeg" || extension == ".bmp" || extension == ".tga") {
		//resource = std::make_shared<Image>(path);
	}
	else if (extension == ".wav" || extension == ".mp3" || extension == ".ogg" || extension == ".flac") {
		//resource = std::make_shared<Audio>(path);
	}
	else {
		// Unsupported file type
		return std::shared_ptr<Resource>{};
	}

	// If resource was created, set its path and add it to the map
	if (resource != nullptr) {
		resource->path = path;
		resources[resourcePath] = resource;
		return resource;
	}
	
	// Something went wrong. Return empty shared pointer
	return std::shared_ptr<Resource>{};
}
std::shared_ptr<it::Resource> it::ResourceManager::load(Resource* resource) {
	// Resource to return
	std::shared_ptr<Resource> sharedResource{};

	// Check if resource is valid
	if (resource == nullptr)
		return sharedResource; // Return empty shared pointer
	if (resource->path.empty() || !std::filesystem::exists(resource->path))
		return sharedResource; // Return empty shared pointer

	// Check if resource already exists
	std::string resourcePath{ resource->path.string() };
	auto iterator{ resources.find(resourcePath) };
	if (iterator != resources.end()) {
		sharedResource = iterator->second;
		if (sharedResource != nullptr)
			return sharedResource;
		return std::shared_ptr<Resource>{};
	}

	// Create shared pointer from raw pointer
	sharedResource = std::shared_ptr<Resource>(resource);

	// If resource was created, add it to the map
	if (sharedResource != nullptr) {
		resources[resourcePath] = sharedResource;
		return sharedResource;
	}

	// Something went wrong. Return empty shared pointer
	return std::shared_ptr<Resource>{};
}
bool it::ResourceManager::unload(const std::filesystem::path& path) {
	// Check if resource exists
	std::string resourcePath{ path.string() };
	auto iterator{ resources.find(resourcePath) };
	if (iterator != resources.end()) {
		std::shared_ptr<Resource> resource{ iterator->second };
		if (resource != nullptr) {
			resources.erase(iterator);
			return true; // Resource unloaded
		}
	}

	// Resource not found
	return false;
}

void it::ResourceManager::clear() {
	resources.clear();
}
