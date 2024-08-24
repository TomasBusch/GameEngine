#include "Engine/Core/Base.hpp"

#include "Application.hpp"

#include "Engine/Runtime/ImGui/ImGuiContext.hpp"

#include "Engine/Runtime/Resources/ShaderModule.hpp"
#include "Engine/Core/Debug/Logger.hpp"

namespace Engine {

	Application* Application::g_Application = nullptr;

	Application& Application::Get()
	{
		ENGINE_ASSERT(g_Application != nullptr, "ERROR: Application was never created.");
		return *g_Application;
	};

	Application::Application(const Specs& specs)
		:m_Specs(specs)
	{
	};

	void Application::Create(Args args) {
		g_Application = CreateApplication(args);
	};

	void Application::Init()
	{
		//Init Window
		Window::Params windowParams{};
		windowParams.width = 640;
		windowParams.height = 480;
		windowParams.RenderAPI = RenderAPI::OPENGL;

		m_Window = Engine::Window::Create(windowParams);
		m_Window->Init();

		//Init Input module
		Input::InputModule::GetInstance()->Init(m_Window.get());

		//Init ImGui context
		//TODO consider moving to window
		m_ImGuiContext = ImGuiContext::Create(m_Window.get());
		m_ImGuiContext->Init("#version 150");

		//Init shader loader module
		//TODO move to Renderer
		Resource::ShaderModule::Get().LoadFile("");

		//Init Client Logger (core logger is initialized before application initilization)
		Client::Logger::Init();

		Core::Logger::Info("OnInit()");
		OnInit();

		m_Initialized = true;
	};

	void Application::Shutdown() {

	};

	Scope<Engine::Window>& Application::GetWindow() {
		return m_Window;
	};

	void Application::Run()
	{
		ENGINE_ASSERT(g_Application->m_Initialized, "ERROR: Application was never initialized. Remember to call Application::Get().Init().");


		while (m_Running)
		{
			m_Window->OnUpdate();
			m_ImGuiContext->BeginFrame();
			ImGuiRender();
			m_ImGuiContext->EndFrame();

		}

		m_Window->Shutdown();
	};

	//void Application::ImGuiRender()
	//{
	//	//static bool show_demo_ui;
	//	//ImGui::ShowDemoWindow(&show_demo_ui);
	//}

	void Application::OnKeyEvent(Input::KeyEvent e)
	{

	}

	void Application::OnTextEvent(Input::TextEvent e)
	{

	}

	void Application::OnMouseScrollEvent(Input::MouseScrollEvent e)
	{

	}

	void Application::OnWindowFocusEvent(WindowFocusEvent e)
	{
		m_Focused = e.Focused;
	}

	void Application::OnMouseCursorEvent(Input::MouseCursorEvent e)
	{

	}

	void Application::OnMouseButtonEvent(Input::MouseButtonEvent e)
	{

	}

	void Application::OnWindowMaximizeEvent(WindowMaximizeEvent e) 
	{
		m_Minimized = !e.Maximized;
	}

	void Application::OnWindowCloseEvent(WindowCloseEvent e)
	{
		m_Running = false;
	}
}
