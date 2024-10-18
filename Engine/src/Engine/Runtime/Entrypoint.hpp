#pragma once

#include "Engine/Core/Base.hpp"
#include "Engine/Runtime/Application.hpp"

extern Engine::Application* Engine::Entrypoint(Application::Args args);

int main(int argc, char* argv[]) {
	Engine::Ref<Engine::Application::AppDependencies> dependencies = Engine::CreateRef<Engine::Application::AppDependencies>();

	//Logger
	Engine::Ref<Engine::Logger> g_Logger = Engine::CreateRef<Engine::Logger>();
	dependencies->logger = g_Logger;
	//Config
	Engine::Ref<Engine::Config> g_Config = Engine::CreateRef<Engine::Config>();
	dependencies->config = g_Config;
	//Filesystem
	//Engine::Ref<Engine::FileSystem> g_FileSystem = Engine::CreateRef<Engine::FileSystem>();
	//dependencies->filesystem = g_FileSystem;


	//Application
	Engine::Application* app = Engine::Entrypoint({ "" });
	
	app->Init(dependencies);
	app->Run();
	app->Shutdown();
}