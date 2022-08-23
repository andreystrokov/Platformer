#pragma once
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <string>
namespace lve
{
	class LveWindow
	{
	public:
		LveWindow(int _width, int _height, std::string _name) :
			width(_width), height(_height), windowName(_name)
		{
			initWindow();
		};
		LveWindow& operator= (const LveWindow&) = delete;
		bool shouldClose() { return glfwWindowShouldClose(window); }
		~LveWindow();
	private:
		void initWindow();
		int width;
		int height;
		std::string windowName;
		GLFWwindow* window;
	};
}