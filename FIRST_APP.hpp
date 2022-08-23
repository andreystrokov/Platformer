#pragma once
#include "lve_window.h"
#include "lve_pipeline.h"
#include <iostream>
namespace lve
{
	class FirstApp
	{
	public:
		static constexpr int width = 800;
		static constexpr int height = 600;
		void run();
	private:
		LveWindow window{ width,height,"PLATFORMER" };
		LvePipeline lvePipeline{ "shaders/vert.spv","shaders/frag.spv" };
	};

};

