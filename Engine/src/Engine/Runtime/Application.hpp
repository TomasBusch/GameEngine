#pragma once
#include "pch.hpp"

#include "Engine/Core/Base.hpp"

#include "Engine/Runtime/Window.hpp"
#include "Engine/ImGui/ImGuiContext.hpp"

#include "Engine/Runtime/Scene/Scene.hpp"

#include "Engine/Events/Event.hpp"
#include "Engine/Events/InputEvents.hpp"
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
			std::string width;
			std::string height;
			RenderAPI render_api;
		};

		struct Specs {
			std::string name;
			std::string workDir;
			Args cmdLineArgs;
		};

		struct AppDependencies {
			Ref<Logger> logger = nullptr;
			Ref<Config> config = nullptr;
		};

	public:
		Application(const Specs& specs);
		virtual ~Application() = default;

		Scope<Engine::Window>& GetWindow();
	private:
		void Init(Ref<AppDependencies> dependencies);
		void Run();
		void Shutdown();
	protected:
		virtual void OnInit() {};

		virtual void ImGuiRender() {};

		virtual void OnKeyEvent(Input::KeyEvent e) override;

		virtual void OnTextEvent(Input::TextEvent e) override;

		virtual void OnMouseScrollEvent(Input::MouseScrollEvent e) override;

		virtual void OnMouseMoveEvent(Input::MouseMoveEvent e) override;

		virtual void OnMouseButtonEvent(Input::MouseButtonEvent e) override;

		virtual void OnWindowCloseEvent(WindowCloseEvent e) override;

		virtual void OnWindowFocusEvent(WindowFocusEvent e) override;

		virtual void OnWindowMaximizeEvent(WindowMaximizeEvent e) override;

	private:
		Specs m_Specs;
		bool m_Running = true;
		bool m_Minimized = false;
		bool m_Initialized = false;
		bool m_Focused = true;

		//Dependencies
		Ref<Engine::Logger> m_Logger = nullptr;
		Ref<Engine::Config> m_Config = nullptr;

		Scope<Engine::Window> m_Window = nullptr;
		Scope<Engine::ImGuiContext> m_ImguiContext = nullptr;

		//--Systems--
		//Scope<Engine::RenderSystem> m_RenderSystem = nullptr;
		//Scope<Engine::AssetSystem> m_AssetManager = nullptr;
		//Scope<Engine::InputSystem> m_InputSystem = nullptr;
		//Scope<Engine::ScriptingSystem> m_ScriptingSystem = nullptr;
		//Scope<Engine::PhysicsSystem> m_PhysicsSystem = nullptr;

		//std::stack<Scene> m_Scenes;

		friend int ::main(int argc, char* argv[]);
	};

	Application* Entrypoint(Application::Args args);
}