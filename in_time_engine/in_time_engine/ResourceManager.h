#pragma once

// Dependencies | std
#include <string>
#include <unordered_map>
#include <filesystem>

// Dependencies | in_time_engine
#include "Resource.h"
#include "Image.h"
//#include "Audio.h"

namespace it {
	class ResourceManager {
		// Friends
		friend class InTimeEngine;
		friend class Resource;

		// Structs
		struct KeyHasher {
			// Operators | ()
			std::size_t operator()(const std::string& key) const;
		};
		struct KeyComperator {
			// Operators | ()
			bool operator()(const std::string& leftResourcePath, const std::string& rightResourcePath) const;
		};

		// Object
		private:
			// Properties
			InTimeEngine* inTimeEngine{ nullptr };
			std::unordered_map<std::string, std::shared_ptr<Resource>, KeyHasher, KeyComperator> resources{};

		public:
			// Constructor / Destructor
			ResourceManager() = default;
			ResourceManager(InTimeEngine* inTimeEngine);
			ResourceManager(const ResourceManager& other) = default;
			ResourceManager& operator=(const ResourceManager& other) = default;
			~ResourceManager() = default;

			// Operators | assignment
			ResourceManager& operator=(ResourceManager&& other) = default;
			ResourceManager(ResourceManager&& other) = default;

			// Getters
			InTimeEngine* getInTimeEngine() const;

			// Functions
			bool has(const std::filesystem::path& path) const;
			std::shared_ptr<Resource> get(const std::filesystem::path& path) const;
			std::shared_ptr<Resource> load(const std::filesystem::path& path);
			std::shared_ptr<Resource> load(Resource* resource);
			bool unload(const std::filesystem::path& path);
			void clear();
	};
}
