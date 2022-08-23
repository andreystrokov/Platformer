#include "lve_pipeline.h"
#include <fstream>
#include <stdexcept>
namespace lve
{	

	LvePipeline::LvePipeline(const std::string& vertFilepath, const std::string& fragFilepath)
	{
		createGraphicsPipeline(vertFilepath, fragFilepath);
	}
	void LvePipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath)
	{
		auto vertCode = readFile(vertFilepath);
		auto fragCode = readFile(fragFilepath);

		std::cout << vertCode.size() << std::endl;
		std::cout << fragCode.size() << std::endl;
	}


	std::vector <char> LvePipeline::readFile(const std::string& filepath)
	{
		std::ifstream file(filepath,std::ios::ate,std::ios::binary);
		if (!file.is_open())
		{
			throw std::runtime_error("ERROR READ FILE " + filepath + "\n");
		}
		size_t fileSize = static_cast<size_t>(file.tellg());

		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(),fileSize);
		return buffer;

	}
}