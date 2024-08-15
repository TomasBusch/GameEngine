#pragma once
#include "pch.h"

#include "Engine/Core/Base.h"

#include "Platform/Window.h"
#include "Engine/Runtime/Systems/Scene/Scene.h"

#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Events/InputEvents.h"

#include "Engine/Core/Events/Subscriber.h"

#include "Engine/Core/Events/EventBus/EventBusTest.h"

int main(int argc, char* argv[]);

namespace Engine {

	class Application {
	public:
		struct Args {
			std::string args;
		};

		struct Specs {
			std::string name;
			std::string workDir;
			Args cmdLineArgs;
		};
	public:
		static Application& Get();

		Application(const Specs& specs);
		virtual ~Application() = default;

		Scope<Engine::Window>& GetWindow();
	private:
		static void Create(Args args);
		void Init();
		void Run();
		void Shutdown();
	private:
		static Application* g_Application;

		Specs m_Specs;
		bool m_Running = true;
		bool m_Minimized = false;
		bool m_Initialized = false;

		Scope<Engine::Window> m_Window = nullptr;

		//std::stack<Scene> m_Scenes;

		friend int ::main(int argc, char* argv[]);
	};

	Application* CreateApplication(Application::Args args);
}