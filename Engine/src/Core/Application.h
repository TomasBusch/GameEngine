#pragma once

#include "pch.h"
#include "Core/Definitions/Memory.h"

#include "Platform/Window.h"
#include <Systems/Scene/Scene.h>

int main(int argc, char* argv[]);

namespace Engine {

	struct AppArgs {
		std::string args;
	};

	struct AppSpecs {
		std::string name;
		std::string workDir;
		AppArgs cmdLineArgs;
	};

	class Application {
	public:
		Application(const AppSpecs& specs);
		virtual ~Application();
		void Init();
		void OnEvent();
	private:
		void Run();
	private:
		AppSpecs m_Specs;
		bool m_Running = true;
		bool m_Minimized = false;

		Scope<Engine::Window> m_Window;

		//std::stack<Scene> m_Scenes;



		friend int ::main(int argc, char* argv[]);
	};

	Application* CreateApplication(AppArgs args);
}