#include <config.h>
#include <Engine.h>

class Sandbox : public Engine::Application 
{
public:
	Sandbox(const Engine::Application::Specs& specs)
		: Engine::Application(specs)
	{

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