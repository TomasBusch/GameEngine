#pragma once
#include "pch.hpp"

#include "Engine/Core/Base.hpp"

#include "Platform/Window.hpp"
#include "Engine/Runtime/Systems/Scene/Scene.hpp"

#include "Engine/Core/Events/Event.hpp"
#include "Engine/Core/Events/InputEvents.hpp"
#include "Engine/Runtime/Input/InputModule.hpp"

int main(int argc, char* argv[]);

namespace Engine {

	class Application : public 
		Input::KeyboardEventsListener,
		Input::MouseEventsListener,
		WindowEventsListener
	{
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

		virtual void OnKeyEvent(Input::KeyEvent e) override;

		virtual void OnTextEvent(Input::TextEvent e) override;

		virtual void OnMouseScrollEvent(Input::MouseScrollEvent e) override;

		virtual void OnMouseCursorEvent(Input::MouseCursorEvent e) override;

		virtual void OnMouseButtonEvent(Input::MouseButtonEvent e) override;

		virtual void OnWindowCloseEvent(WindowCloseEvent e) override;

		virtual void OnWindowFocusEvent(WindowFocusEvent e) override;

		virtual void OnWindowMaximizeEvent(WindowMaximizeEvent e) override;

	private:
		static Application* g_Application;

		Specs m_Specs;
		bool m_Running = true;
		bool m_Minimized = false;
		bool m_Initialized = false;
		bool m_Focused = true;

		Scope<Engine::Window> m_Window = nullptr;

		//std::stack<Scene> m_Scenes;

		friend int ::main(int argc, char* argv[]);
	};

	Application* CreateApplication(Application::Args args);
}