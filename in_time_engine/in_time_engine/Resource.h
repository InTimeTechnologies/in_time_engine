#pragma once

// Dependencies | std
#include <vector>
#include <filesystem>
#include <typeinfo>

namespace it {
	// Forward declarations
	class InTimeEngine;
	class ResourceManager;
	class Resource;

	class Resource {
		// Friends
		friend class ResourceManager;
		friend struct ResourceHasher;
		friend struct ResourceComperator;

		// Object
		protected:
			// Properties
			std::filesystem::path path{};

		public:
			// Constructor / Destructor
			Resource() = default;
			Resource(const std::filesystem::path& path);
			Resource(const Resource& other);
			Resource(Resource&& other) noexcept;
			virtual ~Resource() = default;

			// Operators | assignment
			Resource& operator=(const Resource& other);
			Resource& operator=(Resource&& other) noexcept;

			// Getters
			std::filesystem::path getPath() const;
			virtual const std::type_info& getTypeInfo() const = 0;

			// Setters
			void setPath(const std::filesystem::path& path);
	};
}
