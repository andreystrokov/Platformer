#include "FIRST_APP.hpp"
namespace lve
{
	void FirstApp::run()
	{
		while (!window.shouldClose())
		{	
			glfwPollEvents();
		}
	}
}

