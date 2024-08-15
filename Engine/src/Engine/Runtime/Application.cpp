#include "Engine/Core/Base.h"

#include "Application.h"

#include "Engine/Runtime/ImGui/ImGuiContext.h"

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

		//GameEventBus* gbus = GameEventBus::g_Instance;
		//KeyEventBus* kbus = KeyEventBus::g_Instance;

		GameEventHandler* ghandler = new GameEventHandler();
		KeyEventHandler* khandler = new KeyEventHandler();

		//gbus = GameEventBus::g_Instance;
		//kbus = KeyEventBus::g_Instance;

		GameEvent ge = GameEvent();
		ge.data = 2;
		KeyEvent ke = KeyEvent();
		ke.data = 3;

		GameEventBus::Broadcast(&IGameEvent::OnGameEvent, ge);
		KeyEventBus::Broadcast(&IKeyEvent::OnKeyEvent, ke);

		GameEventBus::QueueBroadcast(&IGameEvent::OnGameEvent, ge);
		KeyEventBus::QueueBroadcast(&IKeyEvent::OnKeyEvent, ke);

		//gbus = GameEventBus::g_Instance;
		//kbus = KeyEventBus::g_Instance;

		GameEventBus::ExecuteQueue();
		KeyEventBus::ExecuteQueue();

		delete ghandler;

		Scope<ImGuiContext> ImGui = ImGuiContext::Create(m_Window.get());
		ImGui->Init("#version 150");
		while (!m_Window->ShouldClose())
		{
			m_Window->OnUpdate();
			ImGui->Render();
		}

		m_Window->Shutdown();
	};
}
