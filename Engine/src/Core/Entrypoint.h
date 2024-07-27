#pragma once

#include "Core/Application.h"

extern Engine::Application* Engine::CreateApplication(AppArgs args);

int main(int argc, char* argv[]) {
	auto app = Engine::CreateApplication({ "" });
	app->Init();
	app->Run();
}