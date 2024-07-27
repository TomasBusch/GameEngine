#include "OpenGLWindow.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

Engine::OpenGLWindow::OpenGLWindow(WindowParams& params)
	:m_Width(params.width), m_Height(params.height), m_WindowHandle(nullptr)
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


	if (!glfwInit())
		return;

	m_WindowHandle = glfwCreateWindow(640, 480, "OpenGL Window", NULL, NULL);
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

GLFWwindow* Engine::OpenGLWindow::GetNativeHandle()
{
	return m_WindowHandle;
}
