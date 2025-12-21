#include "ShaderModule.h"

// Dependencies | std
#include <fstream>

// Dependencies | VulkanEngine
#include "VulkanEngine.h"

// class ShaderModule

// Object | public

// Constructor / Destructor
namespace it {
	it::Vulkan::ShaderModule::~ShaderModule() {
		clearModule();
	}

	// Getters
	VkShaderModule it::Vulkan::ShaderModule::getModule() const {
		return shaderModule;
	}
	std::vector<char> it::Vulkan::ShaderModule::getByteCode() const {
		return byteCode;
	}
	bool it::Vulkan::ShaderModule::isCreated() const {
		return created;
	}

	// Functions
	bool it::Vulkan::ShaderModule::loadByteCode(const std::filesystem::path& pathToFile) {
		byteCode.clear();

		std::ifstream ifstream = std::ifstream(pathToFile, std::ios::ate | std::ios::binary);
		if (!ifstream.is_open())
			return false;

		size_t fileSize = (size_t)ifstream.tellg();
		byteCode.resize(fileSize);

		ifstream.seekg(0);
		ifstream.read(byteCode.data(), fileSize);

		ifstream.close();

		return true;
	}
	bool it::Vulkan::ShaderModule::create() {
		VulkanEngine* vulkanEngine = (VulkanEngine*)VulkanEngine::s_getSingleton();
		if (vulkanEngine == nullptr)
			return false;

		clearModule();

		if (byteCode.size() == 0)
			return false;

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = byteCode.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(byteCode.data());

		VkResult vulkanResult = vkCreateShaderModule(vulkanEngine->vulkanDevice, &createInfo, nullptr, &shaderModule);
		if (vulkanResult != VK_SUCCESS)
			return false;

		created = true;
		return true;
	}
	bool it::Vulkan::ShaderModule::create(const std::filesystem::path& pathToFile) {
		bool success = loadByteCode(pathToFile);
		if (!success)
			return false;

		return create();
	}
	void it::Vulkan::ShaderModule::clearByteCode() {
		byteCode.clear();
	}
	bool it::Vulkan::ShaderModule::clearModule() {
		VulkanEngine* vulkanEngine = (VulkanEngine*)VulkanEngine::s_getSingleton();
		if (vulkanEngine == nullptr)
			return false;

		if (created) {
			vkDestroyShaderModule(vulkanEngine->vulkanDevice, shaderModule, nullptr);
			created = false;
		}

		return true;
	}
	bool it::Vulkan::ShaderModule::clear() {
		clearByteCode();
		return clearModule();
	}
}
