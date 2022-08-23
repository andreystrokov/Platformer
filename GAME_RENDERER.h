#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>
#include <optional>

#define STD_OUTPUT std::cout
#define STD_ENDL std::endl

namespace GAME_RENDERER
{	
	struct QueueFamilyIndices { // индексы семейств очередей
		std::optional<uint32_t> graphicsFamily;
		bool isComplete() {
			return graphicsFamily.has_value();
		}
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
		
		void mainLoop();
		void cleanup();
		void run();


		// Отладочные слои валидации
		bool checkValidationLayerSupport();
		std::vector<const char*> getRequiredExtensions();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
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
		const int WIDTH;
		const int HEIGHT;
		const std::string name;

		GLFWwindow* mainWindow;
		// Vulkan debug
		VkDebugUtilsMessengerEXT debugMessenger;
		// VULKAN ELEMENTS
		VkInstance instance;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;
	};


}
