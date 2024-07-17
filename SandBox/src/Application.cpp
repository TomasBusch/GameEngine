#include <iostream>
#include <Engine.h>
#include <config.h>
#include <fstream>
#include <filesystem>

int main(int argc, char* argv[])
{
	std::ofstream file;
	
	file.open("res/test.txt");
	if (file.is_open()) {
		file << "test data ";

		std::cout << VulkanEngine::cmake::project_name << "SandBox" << returnTwo() << std::endl << std::endl;
	}

	std::cout << std::filesystem::current_path() << std::endl;
	std::cout << argv[0] << std::endl;

	return 0;
}