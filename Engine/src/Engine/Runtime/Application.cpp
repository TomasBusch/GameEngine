#include "Engine/Core/Base.hpp"

#include "Application.hpp"

#include "Engine/Runtime/Resources/ShaderModule.hpp"
#include "Engine/Core/Debug/Logger.hpp"

namespace Engine {

	Application::Application(const Specs& specs)
		:m_Specs(specs)
	{
	};

	void Application::Init(Ref<AppDependencies> dependencies)
	{
		m_Logger = dependencies->logger;
		m_Config = dependencies->config;

		//Init Window
		Window::Params windowParams{};
		windowParams.width = 640;
		windowParams.height = 480;
		windowParams.renderAPI = RenderAPI::OPENGL;

		m_Window = Engine::Window::Create(windowParams);
		m_Window->Init();

		m_ImguiContext = Engine::ImGuiContext::Create(m_Window.get());
		m_ImguiContext->Init();

		//Init Input module
		Input::InputModule::GetInstance()->Init(m_Window.get());

		//m_Window->InitImGui();

		//Init ImGui context
		//TODO consider moving to window
		//m_ImGuiContext = ImGuiContext::Create(m_Window.get());
		//m_ImGuiContext->Init("#version 150");

		//Init shader loader module
		//TODO move to Renderer
		Resource::ShaderModule::Get().LoadFile("");
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
		ENGINE_CORE_ASSERT(m_Initialized, "ERROR: Application was never initialized. Remember to call Application::Init()");


		while (m_Running)
		{
			m_Window->OnUpdate();
			m_ImguiContext->BeginFrame();
			ImGuiRender();
			m_ImguiContext->EndFrame();

		}

		m_Window->Shutdown();
	};

	//void Application::ImGuiRender()
	//{
	//	static bool show_demo_ui;
	//	ImGui::ShowDemoWindow(&show_demo_ui);
	//}

	void Application::OnKeyEvent(Input::KeyEvent e)
	{
		if (e.Key == Input::KeyCode::ESCAPE) {
			Input::InputModule::GetInstance()->StartTextInput();
		}

		if (e.Key == Input::KeyCode::BACKSPACE) {
			Input::InputModule::GetInstance()->StopTextInput();
		}
	}

	void Application::OnTextEvent(Input::TextEvent e)
	{
		std::cout << (char)e.UnicodeCode << std::endl;
	}

	void Application::OnMouseScrollEvent(Input::MouseScrollEvent e)
	{

	}

	void Application::OnWindowFocusEvent(WindowFocusEvent e)
	{
		m_Focused = e.Focused;
	}

	void Application::OnMouseMoveEvent(Input::MouseMoveEvent e)
	{

	}

	void Application::OnMouseButtonEvent(Input::MouseButtonEvent e)
	{

	}

	void Application::OnWindowMaximizeEvent(WindowMaximizeEvent e) 
	{
		m_Minimized = false;
	}

	void Application::OnWindowCloseEvent(WindowCloseEvent e)
	{
		m_Running = false;
	}
}
