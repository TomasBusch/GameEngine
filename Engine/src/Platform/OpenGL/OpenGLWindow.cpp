#include "OpenGLWindow.hpp"

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

	SetCallbacks();

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

void Engine::OpenGLWindow::SetCallbacks()
{
	auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
		FramebufferSizeEvent e = FramebufferSizeEvent(width, height);
		WindowEventsBus::Broadcast(&IWindowEvents::OnFramebufferSizeEvent, e);
	};

	auto window_close_callback = [](GLFWwindow* window) {
		WindowCloseEvent e = WindowCloseEvent();
		WindowEventsBus::Broadcast(&IWindowEvents::OnWindowCloseEvent, e);
	};

	auto window_pos_callback = [](GLFWwindow* window, int xpos, int ypos) {
		WindowPositionEvent e = WindowPositionEvent(xpos, ypos);
		WindowEventsBus::Broadcast(&IWindowEvents::OnWindowPositionEvent, e);
	};

	auto window_size_callback = [](GLFWwindow* window, int width, int height) {
		WindowSizeEvent e = WindowSizeEvent(width, height);
		WindowEventsBus::Broadcast(&IWindowEvents::OnWindowSizeEvent, e);
	};

	auto window_content_scale_callback = [](GLFWwindow* window, float xscale, float yscale) {
		WindowContentScaleEvent e = WindowContentScaleEvent(xscale, yscale);
		WindowEventsBus::Broadcast(&IWindowEvents::OnWindowContentScaleEvent, e);
	};

	auto window_focus_callback = [](GLFWwindow* window, int focused) {
		WindowFocusEvent e = WindowFocusEvent(focused);
		WindowEventsBus::Broadcast(&IWindowEvents::OnWindowFocusEvent, e);
	};

	auto window_iconify_callback = [](GLFWwindow* window, int iconified) {
		WindowIconifyEvent e = WindowIconifyEvent(iconified);
		WindowEventsBus::Broadcast(&IWindowEvents::OnWindowIconifyEvent, e);
	};

	auto window_maximize_callback = [](GLFWwindow* window, int maximized) {
		WindowMaximizeEvent e = WindowMaximizeEvent(maximized);
		WindowEventsBus::Broadcast(&IWindowEvents::OnWindowMaximizeEvent, e);
	};

	auto window_refresh_callback = [](GLFWwindow* window) {
		WindowRefreshEvent e = WindowRefreshEvent();
		WindowEventsBus::Broadcast(&IWindowEvents::OnWindowRefreshEvent, e);
	};

	glfwSetFramebufferSizeCallback(m_WindowHandle, framebuffer_size_callback);
	glfwSetWindowCloseCallback(m_WindowHandle, window_close_callback);
	glfwSetWindowPosCallback(m_WindowHandle, window_pos_callback);
	glfwSetWindowSizeCallback(m_WindowHandle, window_size_callback);
	glfwSetWindowContentScaleCallback(m_WindowHandle, window_content_scale_callback);
	glfwSetWindowFocusCallback(m_WindowHandle, window_focus_callback);
	glfwSetWindowIconifyCallback(m_WindowHandle, window_iconify_callback);
	glfwSetWindowMaximizeCallback(m_WindowHandle, window_maximize_callback);
	glfwSetWindowRefreshCallback(m_WindowHandle, window_refresh_callback);
}
