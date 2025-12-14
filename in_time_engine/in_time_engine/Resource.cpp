#include "Resource.h"

// class it::Resource

// Object | public

// Constructor / Destructor
it::Resource::Resource(const std::filesystem::path& path) : path(path) {

}
it::Resource::Resource(const Resource& other) : path(other.path) {

}
it::Resource::Resource(Resource&& other) noexcept : path(other.path) {
	other.path.clear();
}

// Operators | assignment
it::Resource& it::Resource::operator=(const Resource& other) {
	if (this != &other)
		path = other.path;

	return *this;
}
it::Resource& it::Resource::operator=(Resource&& other) noexcept {
	if (this != &other) {
		path = other.path;
		other.path.clear();
	}

	return *this;
}

// Getters
std::filesystem::path it::Resource::getPath() const {
	return path;
}

// Setters
void it::Resource::setPath(const std::filesystem::path& path) {
	this->path = path;
}
