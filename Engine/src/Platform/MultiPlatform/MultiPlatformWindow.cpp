/*
#include "MultiPlatformWindow.h"
#include "RenderAPI/Context.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

Engine::MultiplatformWindow::MultiplatformWindow()
{

}

Engine::MultiplatformWindow::~MultiplatformWindow()
{

}

void Engine::MultiplatformWindow::Init()
{
	//--Hints--
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);


	if (!glfwInit())
		return;

	m_WindowHandle = glfwCreateWindow(640, 480, "Window Title", NULL, NULL);
	if (!m_WindowHandle)
	{
		glfwTerminate();
		return;
	}

	//glfwMakeContextCurrent(m_WindowHandle);
}

void Engine::MultiplatformWindow::OnUpdate()
{
	glfwSwapBuffers(m_WindowHandle);
}

void Engine::MultiplatformWindow::Shutdown()
{
	glfwTerminate();
}

bool Engine::MultiplatformWindow::ShouldClose()
{
	return glfwWindowShouldClose(m_WindowHandle);
}

Engine::Scope<Engine::Context>& Engine::MultiplatformWindow::GetContext()
{
	return m_Context;
}

GLFWwindow* Engine::MultiplatformWindow::GetNativeHandle()
{
	return m_WindowHandle;
}
*/