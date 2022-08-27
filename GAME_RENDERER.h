#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <optional>
#include <set>
#include <fstream>
#include <thread>
#include <array>
#include <bitset>

#define STD_OUTPUT std::cout
#define STD_ENDL std::endl

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace GAME_RENDERER
{	

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
			// привязка вершин
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);
			// привязка цвета
			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);
			return attributeDescriptions;
		}
	};

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};
	

	const std::vector<Vertex> vertices = {
		{{-1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
	{{1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}},
	{{1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
	{{-1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}
	};
	const std::vector<uint16_t> indices =
	{
		0,1,2,2,3,0
	};

	struct QueueFamilyIndices { // индексы семейств очередей
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;
		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	class GAME_RENDERER
	{
	public:
		GAME_RENDERER(int _width, int _height, std::string _name) :
			WIDTH{ _width }, HEIGHT{ _height }, name{ _name } {}
		~GAME_RENDERER() { cleanup(); }
		void initWindow();

		void initVulkan();
			void createInstance();
			void setupDebugMessenger();
			// настройка физического девайса
			void pickPhysicalDevice();
				bool isDeviceSuitable(VkPhysicalDevice device);
				QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
			// настройка логического девайса
			void createLogicalDevice();
			void createSurface();
				bool checkDeviceExtensionSupport(VkPhysicalDevice device);
			void CreateSwapChain();
				SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
				VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
				VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
				VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			void createImageViews();
			void createGraphicsPipeline();
			VkShaderModule createShaderModule(const std::vector<char>& code);
			void createRenderPass();
			void createFrameBuffers();
			void createCommandPool();

			void createVertexBuffer();
			void createIndexBuffer();
			
			uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
			void createCommandBuffers();
			void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
			void drawFrame();
			void createSyncObjects();

			void recreateSwapChain();
			void cleanupSwapChain();
			void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
			void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
			void createDescriptorSetLayout();
			void createUniformBuffers();
			void updateUniformBuffer(uint32_t currentImage);


			static std::vector<char> readFile(const std::string& filename);

		void mainLoop();
		void cleanup();
		void run();


		// Отладочные слои валидации
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
															VkDebugUtilsMessageTypeFlagsEXT messageType,
															const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
															void* pUserData);
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
										      const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
											  const VkAllocationCallbacks* pAllocator,
											  VkDebugUtilsMessengerEXT* pDebugMessenger);
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
		void DestroyDebugUtilsMessengerEXT(VkInstance instance,
										   VkDebugUtilsMessengerEXT debugMessenger,
										   const VkAllocationCallbacks* pAllocator);
	private:
		int WIDTH;
		int HEIGHT;
		std::string name;

		GLFWwindow* mainWindow;
		// Vulkan debug
		VkDebugUtilsMessengerEXT debugMessenger;
		// VULKAN ELEMENTS
		VkInstance instance;
		VkPhysicalDevice physicalDevice;
		VkDevice device;
		VkSurfaceKHR surface;
		VkQueue graphicsQueue;
		VkQueue presentQueue;
		VkSwapchainKHR swapChain;
			std::vector<VkImage> swapChainImages;
			std::vector<VkImageView> swapChainImageViews;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;

		VkDescriptorSetLayout descriptorSetLayout;
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;


		VkPipelineLayout pipelineLayout;
		VkRenderPass renderPass;
		VkPipeline graphicsPipeline;
		std::vector<VkFramebuffer> swapChainFramebuffers;
			VkCommandPool commandPool;
			std::vector<VkCommandBuffer> commandBuffers;
			const int MAX_FRAMES_IN_FLIGHT = 2;

		// Буфер вершин
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		// Индексный буфер
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;


		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		std::vector<VkFence> imagesInFlight;
		size_t currentFrame = 0;
	};


}
