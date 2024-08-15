#pragma once

#include "Engine/Runtime/Application.h"

extern Engine::Application* Engine::CreateApplication(Application::Args args);

int main(int argc, char* argv[]) {
	Engine::Application::Create({""});
	bool test = true;
	Engine::Application::Get().Init();
	Engine::Application::Get().Run();
	Engine::Application::Get().Shutdown();
}