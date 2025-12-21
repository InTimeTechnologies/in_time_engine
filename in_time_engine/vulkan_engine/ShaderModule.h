#pragma once

// Dependencies | std
#include <filesystem>
#include <vector>

// Dependencies | Vulkan
#include "vulkan/vulkan.h"

namespace it {
	namespace Vulkan {
		class ShaderModule {
			// Object
			private:
				// Properties
				VkShaderModule shaderModule{};
				std::vector<char> byteCode = std::vector<char>(0);
				bool created = false;

			public:
				// Constructor / Destructor
				ShaderModule() = default;
				~ShaderModule();

				// Getters
				VkShaderModule getModule() const;
				std::vector<char> getByteCode() const;
				bool isCreated() const;

				// Functions
				bool loadByteCode(const std::filesystem::path& pathToFile);
				bool create();
				bool create(const std::filesystem::path& pathToFile);
				void clearByteCode();
				bool clearModule();
				bool clear();
		};
	}
}
