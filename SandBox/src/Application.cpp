#include <config.hpp>
#include <Engine.hpp>

#include <filesystem>

class Sandbox : public Engine::Application 
{
public:
	Sandbox(const Engine::Application::Specs& specs)
		: Engine::Application(specs)
	{
		std::filesystem::path cwd = std::filesystem::current_path();
		std::cout << cwd << std::endl;
	}

	~Sandbox() 
	{

	}
};

Engine::Application* Engine::CreateApplication(Engine::Application::Args args) 
{
	Application::Specs specs;
	specs.name = "Vulkan Engine";
	specs.workDir = "./";
	specs.cmdLineArgs = args;

	return new Sandbox(specs);
}