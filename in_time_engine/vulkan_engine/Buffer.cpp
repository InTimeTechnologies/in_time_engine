#include "Buffer.h"

// Dependencies | std
#include <cassert>
#include <cstring>

// Dependencies | VulkanEngine
#include "VulkanEngine.h"

// class Buffer

// Functions
uint32_t IT::Vulkan::Buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VulkanEngine* singleton = (VulkanEngine*)VulkanEngine::s_getSingleton();
	if (singleton == nullptr)
		return 0U;

	VkPhysicalDevice physicalDevice = singleton->physicalDevice;
	if (physicalDevice == nullptr)
		return 0U;

	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	return 0U;
}

// Object | public

// Constructor / Destructor
IT::Vulkan::Buffer::Buffer(const VkBufferCreateInfo& createInfo) {
	create(createInfo);
}
IT::Vulkan::Buffer::Buffer(const VkBufferCreateInfo& createInfo, void* data, size_t dataOffset, size_t dataSize) {
	create(createInfo, data, dataOffset, dataSize);
}
IT::Vulkan::Buffer::Buffer(const VkBufferCreateInfo& createInfo, void* data, size_t dataOffset, size_t dataSize, VkMemoryPropertyFlags memoryPropertyFlags) {
	create(createInfo, data, dataOffset, dataSize, memoryPropertyFlags);
}
IT::Vulkan::Buffer::~Buffer() {
	release();
}

// Getters
VkBuffer IT::Vulkan::Buffer::getBuffer() const {
	return buffer;
}

// Functions
bool IT::Vulkan::Buffer::isCreated() const {
	return buffer == nullptr ? false : true;
}
bool IT::Vulkan::Buffer::create(const VkBufferCreateInfo& createInfo) {
	return create(createInfo, nullptr, 0ULL, 0ULL);
}
bool IT::Vulkan::Buffer::create(const VkBufferCreateInfo& createInfo, void* data, size_t dataOffset, size_t dataSize) {
	return create(createInfo, data, dataOffset, dataSize, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
}
bool IT::Vulkan::Buffer::create(const VkBufferCreateInfo& createInfo, void* data, size_t dataOffset, size_t dataSize, VkMemoryPropertyFlags memoryPropertyFlags) {
	// If previously created
	if (created)
		release(); // Release all previously allocated GPU resources

	// Get Vulkan engine
	VulkanEngine* singleton = (VulkanEngine*)VulkanEngine::s_getSingleton();
	if (singleton == nullptr)
		return false; // Fail: Vulkan engine was not found.

	// Get Vulkan device
	VkDevice vulkanDevice = singleton->vulkanDevice;
	if (vulkanDevice == nullptr)
		return false;

	// Create buffer
	VkResult result = vkCreateBuffer(vulkanDevice, &createInfo, nullptr, &buffer);
	if (result != VK_SUCCESS)
		return false; // Fail: Failed to create buffer.

	// Get memory requirements
	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(vulkanDevice, buffer, &memoryRequirements);

	// Get memory allocation info
	VkMemoryAllocateInfo memoryAllocateInfo{};
	memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memoryAllocateInfo.allocationSize = memoryRequirements.size;
	memoryAllocateInfo.memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, memoryPropertyFlags);

	// Allocate memory
	result = vkAllocateMemory(vulkanDevice, &memoryAllocateInfo, nullptr, &deviceMemory);
	if (result != VK_SUCCESS)
		return false;

	// If there is data to write to GPU buffer
	if (data != nullptr && dataSize > 0) {
		// Bind buffer
		vkBindBufferMemory(vulkanDevice, buffer, deviceMemory, 0);

		// Upload data to GPU
		void* intermediateMemory = nullptr;                                                    // Address to data to upload to GPU
		vkMapMemory(vulkanDevice, deviceMemory, dataOffset, dataSize, 0, &intermediateMemory); // Request an address to write data to
		memcpy(intermediateMemory, data, dataSize);                                            // Write data to requested address
		vkUnmapMemory(vulkanDevice, deviceMemory);                                             // Upload data to GPU
	}

	created = true; // Update flag
	return true; // Success
}

void IT::Vulkan::Buffer::release() {
	if (!isCreated())
		return; // Success: There is nothing to release.

	VulkanEngine* singleton = (VulkanEngine*)VulkanEngine::s_getSingleton();
	if (singleton == nullptr)
		return; // Fail: Vulkan engine was not found.

	VkDevice vulkanDevice = singleton->vulkanDevice;
	if (vulkanDevice == nullptr)
		return;

	vkDestroyBuffer(vulkanDevice, buffer, nullptr);
	buffer = nullptr;

	vkFreeMemory(vulkanDevice, deviceMemory, nullptr);

	created = false; // Update flag
}
