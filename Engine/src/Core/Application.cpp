#include "Application.h"
#include "GUI/ImguiOpenGLContext.h"

Engine::Application::Application(const AppSpecs& specs)
	:m_Specs(specs)
{

}

Engine::Application::~Application()
{

}

void Engine::Application::Init()
{
	WindowParams windowParams{};
	windowParams.width = 600;
	windowParams.height = 400;
	m_Window = Engine::Window::Create(windowParams);
	m_Window->Init();
}

void Engine::Application::Run()
{
	ImguiOpenGLContext Imgui;
	Imgui.Init( (OpenGLWindow*)(m_Window.get()), "#version 100");
	while (!m_Window->ShouldClose())
	{
		m_Window->OnUpdate();
		Imgui.Render();
	}

	m_Window->Shutdown();
}


