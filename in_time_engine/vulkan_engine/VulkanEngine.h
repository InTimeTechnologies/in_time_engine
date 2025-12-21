#pragma once

// Dependencies | std
#include <string>
#include <vector>
#include <optional>
#include <set>

// Dependencies | Vulkan
#include <vulkan/vulkan.h>

// Dependencies | GLFW
#include <glfw/glfw3.h>

// Dependencies | VulkanEngine
#include "ShaderModule.h"
#include "Buffer.h"

// Temp
#include <glm/glm.hpp>
#include <array>

namespace it {
	namespace Vulkan {
		class VulkanEngine {
			// Structures
			public:
				struct QueueFamilyIndices {
					std::optional<uint32_t> graphicsFamily;
					std::optional<uint32_t> presentFamily;

					bool isComplete() const {
						return graphicsFamily.has_value() && presentFamily.has_value();
					}
				};

				struct SwapChainSupportDetails {
					VkSurfaceCapabilitiesKHR capabilities;
					std::vector<VkSurfaceFormatKHR> formats;
					std::vector<VkPresentModeKHR> presentModes;
				};

				// Temp
				struct Vertex {
					glm::vec2 pos;
					glm::vec3 color;

					static VkVertexInputBindingDescription getBindingDescription() {
						VkVertexInputBindingDescription bindingDescription{};
						bindingDescription.binding = 0;
						bindingDescription.stride = sizeof(Vertex);
						bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

						return bindingDescription;
					}
					static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
						std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
						attributeDescriptions[0].binding = 0;
						attributeDescriptions[0].location = 0;
						attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
						attributeDescriptions[0].offset = offsetof(Vertex, pos);

						attributeDescriptions[1].binding = 0;
						attributeDescriptions[1].location = 1;
						attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
						attributeDescriptions[1].offset = offsetof(Vertex, color);

						return attributeDescriptions;
					}
				};

			// Static
			private:
				// Properties
				static VulkanEngine* s_singleton;
				static std::vector<const char*> s_validationLayersToEnable;
				static std::vector<std::string> s_availableValidationLayers;
				static std::vector<const char*> s_extensionsToEnable;

				// Functions
				static std::vector<const char*> s_getGLFWRequiredExtensions();

			public:
				// Properties
				static bool s_enableValidationLayers;

				// Getters
				static VulkanEngine* s_getSingleton();
				static std::vector<std::string> s_getAvailableValidationLayers();
				static std::vector<const char*> s_getValidationLayersToEnable();

				// Functions
				static void s_init();

			// Object
			public:
				// Properties
				bool error = false;
				std::string errorMessage = std::string("None");

				// Properties
				GLFWwindow* glfwWindow = nullptr;

				VkApplicationInfo applicationInfo{};
				VkInstance instance;
				VkDebugUtilsMessengerEXT debugMessenger;
				VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; // Deleted through VkInstance object when it is deleted
				VkDevice vulkanDevice;
				VkQueue graphicsQueue; // Deleted through VkInstance object when it is deleted
				VkSurfaceKHR surface;
				VkQueue presentQueue;
				VkSwapchainKHR swapChain;
				std::vector<VkImage> swapChainImages;
				VkFormat swapChainImageFormat;
				VkExtent2D swapChainExtent;

				std::vector<VkImageView> swapChainImageViews;


				VkPipelineLayout pipelineLayout;
				VkRenderPass renderPass;
				VkPipeline graphicsPipeline;
				std::vector<VkFramebuffer> swapChainFramebuffers;
				VkCommandPool commandPool;
				std::vector<VkCommandBuffer> commandBuffers;

				std::vector<VkSemaphore> imageAvailableSemaphores;
				std::vector<VkSemaphore> renderFinishedSemaphores;
				std::vector<VkFence> inFlightFences;

				const int MAX_FRAMES_IN_FLIGHT = 2;
				uint32_t currentFrame = 0U;

				bool framebufferResized = false;
				bool shouldRender = true;

				Buffer* vertexBuffer;

				// Temp
				const std::vector<Vertex> vertices = {
					{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
					{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
					{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
				};


				// Functions
				void createVulkanInstance();
				void initDebugMessenger();
				void pickPhysicalDevice();
				bool isPhysicalDeviceSuitable(VkPhysicalDevice device);
				QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice);
				void createLogicalDevice();
				void createSurface();
				bool checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice);
				SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
				VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
				VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
				VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
				void createSwapChain();
				void createImageViews();

				void createRenderPass();
				void createGraphicsPipeline();
				void createFrameBuffers();
				void createCommandPool();
				void createCommandBuffer();

				void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

				void createSyncObjects();

				void cleanupSwapChain();
				void recreateSwapChain();

				void createVertexBuffer();

			public:
				// Constructor / Destructor
				VulkanEngine(GLFWwindow* glfwWindow);
				~VulkanEngine();

				// Functions
				void render();
				void onSurfaceResize(int width, int height);
			};
	}
}
