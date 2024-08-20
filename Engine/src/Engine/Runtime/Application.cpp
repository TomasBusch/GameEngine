#include "Engine/Core/Base.hpp"

#include "Application.hpp"

#include "Engine/Runtime/ImGui/ImGuiContext.hpp"

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
		Window::Params windowParams{};
		windowParams.width = 640;
		windowParams.height = 480;
		windowParams.RenderAPI = RenderAPI::OPENGL;
		m_Window = Engine::Window::Create(windowParams);
		m_Window->Init();

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

		Input::InputModule::GetInstance()->Init(m_Window.get());

		Scope<ImGuiContext> ImGui = ImGuiContext::Create(m_Window.get());
		ImGui->Init("#version 150");
		while (m_Running)
		{
			m_Window->OnUpdate();
			ImGui->Render();
		}

		m_Window->Shutdown();
	};

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
