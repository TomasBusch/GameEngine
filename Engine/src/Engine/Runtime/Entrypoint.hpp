#pragma once

#include "Engine/Runtime/Application.hpp"
#include "Engine/Core/Debug/Logger.hpp"
#include "Engine/Core/Debug/Assert.hpp"

extern Engine::Application* Engine::CreateApplication(Application::Args args);

int main(int argc, char* argv[]) {
	Engine::Core::Logger::Init();

	Engine::Application::Create({""});
	bool test = true;
	Engine::Application::Get().Init();
	Engine::Application::Get().Run();
	Engine::Application::Get().Shutdown();
}