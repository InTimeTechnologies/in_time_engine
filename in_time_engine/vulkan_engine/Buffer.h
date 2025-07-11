#pragma once

// Dependencies | Vulkan
#include <vulkan/vulkan.h>

namespace it {
	namespace Vulkan {
		class Buffer {
			// Static
			private:
				// Functions
				static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

			// Object
			private:
				// Properties
				VkBuffer buffer = nullptr;
				VkDeviceMemory deviceMemory = nullptr;
				bool created = false;

			public:
				// Constructor / Destructor
				Buffer() = default;
				Buffer(const VkBufferCreateInfo& createInfo);
				Buffer(const VkBufferCreateInfo& createInfo, void* data, size_t dataOffset, size_t dataSize);
				Buffer(const VkBufferCreateInfo& createInfo, void* data, size_t dataOffset, size_t dataSize, VkMemoryPropertyFlags memoryPropertyFlags);
				~Buffer();

				// Delete other constructors (these will be implemented later)
				Buffer(const Buffer&) = delete;            // No copy constructor
				Buffer& operator=(const Buffer&) = delete; // No copy assignment
				Buffer(Buffer&&) = delete;                 // No move constructor
				Buffer& operator=(Buffer&&) = delete;      // No move assignment

				// Getters
				VkBuffer getBuffer() const;

				// Functions
				bool isCreated() const;
				bool create(const VkBufferCreateInfo& createInfo);
				bool create(const VkBufferCreateInfo& createInfo, void* data, size_t dataOffset, size_t dataSize);
				bool create(const VkBufferCreateInfo& createInfo, void* data, size_t dataOffset, size_t dataSize, VkMemoryPropertyFlags memoryPropertyFlags);
				void release();
		};
	}
}
