#include "OpenGLWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

Engine::OpenGLWindow::OpenGLWindow(Window::Params& params)
	:m_Width(params.width), m_Height(params.height), m_WindowHandle(nullptr), Window(params)
{

}

Engine::OpenGLWindow::~OpenGLWindow()
{

}

void Engine::OpenGLWindow::Init()
{
	//--Hints--
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


	if (!glfwInit())
		return;

	m_WindowHandle = glfwCreateWindow(m_Width, m_Height, "OpenGL Window", NULL, NULL);
	if (!m_WindowHandle)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_WindowHandle);

	gladLoadGL(glfwGetProcAddress);
}

void Engine::OpenGLWindow::OnUpdate()
{
	glfwSwapBuffers(m_WindowHandle);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwPollEvents();
}

void Engine::OpenGLWindow::Shutdown()
{
	//TODO check if this is the last glfw window open
	glfwTerminate();
}

bool Engine::OpenGLWindow::ShouldClose()
{
	return glfwWindowShouldClose(m_WindowHandle);
}

uint32_t Engine::OpenGLWindow::GetWidth()
{
	return m_Width;
}

uint32_t Engine::OpenGLWindow::GetHeight()
{
	return m_Height;
}

void* Engine::OpenGLWindow::getNativeHandle()
{
	return m_WindowHandle;
}
