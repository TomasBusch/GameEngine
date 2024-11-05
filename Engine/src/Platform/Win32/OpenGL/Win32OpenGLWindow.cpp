#ifdef WIN_32
#include "Platform/RenderAPIs/OpenGL/OpenGLWindow.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace Engine {
	OpenGLWindow::OpenGLWindow(Window::Params& params)
	 : Window(params) 
	{

	}

	OpenGLWindow::~OpenGLWindow()
	{
		Shutdown();
	}

	void OpenGLWindow::Init()
	{
		//--Hints--
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		if (!glfwInit())
			return;

		m_PlatformData = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		if (!m_PlatformData)
		{
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent((GLFWwindow*)m_PlatformData);

		glfwSwapInterval(m_Vsync);

		//TODO: Move to the RenderContext
		gladLoadGL(glfwGetProcAddress);

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

		auto window_minimize_callback = [](GLFWwindow* window, int restored) {
			WindowMinimizeEvent e = WindowMinimizeEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowMinimizeEvent, e);
			if (restored == GLFW_TRUE) {
				WindowRestoreEvent e = WindowRestoreEvent();
				WindowEventsBus::Broadcast(&IWindowEvents::OnWindowRestoreEvent, e);
			}
			};

		auto window_maximize_callback = [](GLFWwindow* window, int restored) {
			WindowMaximizeEvent e = WindowMaximizeEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowMaximizeEvent, e);
			if (restored == GLFW_TRUE) {
				WindowRestoreEvent e = WindowRestoreEvent();
				WindowEventsBus::Broadcast(&IWindowEvents::OnWindowRestoreEvent, e);
			}
			};

		auto window_refresh_callback = [](GLFWwindow* window) {
			WindowRefreshEvent e = WindowRefreshEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowRefreshEvent, e);
			};

		glfwSetFramebufferSizeCallback((GLFWwindow*)m_PlatformData, framebuffer_size_callback);
		glfwSetWindowCloseCallback((GLFWwindow*)m_PlatformData, window_close_callback);
		glfwSetWindowPosCallback((GLFWwindow*)m_PlatformData, window_pos_callback);
		glfwSetWindowSizeCallback((GLFWwindow*)m_PlatformData, window_size_callback);
		glfwSetWindowContentScaleCallback((GLFWwindow*)m_PlatformData, window_content_scale_callback);
		glfwSetWindowFocusCallback((GLFWwindow*)m_PlatformData, window_focus_callback);
		glfwSetWindowIconifyCallback((GLFWwindow*)m_PlatformData, window_minimize_callback);
		glfwSetWindowMaximizeCallback((GLFWwindow*)m_PlatformData, window_maximize_callback);
		glfwSetWindowRefreshCallback((GLFWwindow*)m_PlatformData, window_refresh_callback);
	}

	void OpenGLWindow::OnUpdate()
	{
		glfwSwapBuffers((GLFWwindow*)m_PlatformData);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	}

	void OpenGLWindow::Shutdown()
	{
		//TODO check if this is the last glfw window open
		glfwTerminate();
	}

	bool OpenGLWindow::ShouldClose()
	{
		return glfwWindowShouldClose((GLFWwindow*)m_PlatformData);
	}

	void* OpenGLWindow::getNativeHandle()
	{
		return (GLFWwindow*)m_PlatformData;
	}

	void OpenGLWindow::SetWindowGrabInput(bool grab)
	{

	}
}


#endif //WIN_32