#include <config.h>
#include <include/Engine.h>

class Sandbox : public Engine::Application 
{
public:
	Sandbox(const Engine::AppSpecs& specs)
		: Engine::Application(specs)
	{

	}

	~Sandbox() 
	{

	}
};

Engine::Application* Engine::CreateApplication(Engine::AppArgs args) 
{
	AppSpecs specs;
	specs.name = "Vulkan Engine";
	specs.workDir = "./";
	specs.cmdLineArgs = args;

	return new Sandbox(specs);
}