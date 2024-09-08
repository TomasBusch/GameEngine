#include "SDL3OpenGLWindow.hpp"


#include <glad/gl.h>
#include <SDL3/SDL_events.h>

namespace Engine {

	struct SystemEventsCallbacks {
		std::function<void(int, int)> framebuffer_size_callback;

		std::function<void(void)> window_close_callback;

		std::function<void(int, int)> window_pos_callback;

		std::function<void(int, int)> window_size_callback;

		std::function<void(float, float)> window_content_scale_callback;

		std::function<void(int)> window_focus_callback;

		std::function<void(void)> window_restore_callback;

		std::function<void(void)> window_minimize_callback;

		std::function<void(void)> window_maximize_callback;

		std::function<void(void)> window_refresh_callback;
	};

	static SystemEventsCallbacks g_SystemEventCallbacks;

	OpenGLWindow::OpenGLWindow(Window::Params& params)
		:m_Width(params.width), m_Height(params.height), m_WindowHandle(nullptr), m_OpenGLContext(nullptr), Window(params)
	{

	}

	OpenGLWindow::~OpenGLWindow()
	{

	}

	void OpenGLWindow::Init()
	{

		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD))
		{
			ENGINE_CORE_BREAK("Failed to initialized SDL3");
		}

		//TODO: Handle errors with SDL_GetError()

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		Uint32 window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
		m_WindowHandle = SDL_CreateWindow("OpenGL Window", m_Width, m_Height, window_flags);

		if (!m_WindowHandle)
		{
			ENGINE_CORE_BREAK("Failed to create an SDL3 window");
		}

		SDL_SetWindowPosition(m_WindowHandle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		*m_OpenGLContext = SDL_GL_CreateContext(m_WindowHandle);
		SDL_GL_MakeCurrent(m_WindowHandle, *m_OpenGLContext);
		SDL_ShowWindow(m_WindowHandle);

		//SDL_GL_SetSwapInterval(1); // Enable vsync

		gladLoadGL(SDL_GL_GetProcAddress);

		SetCallbacks();
	}

	void OpenGLWindow::OnUpdate()
	{
		SDL_GL_SwapWindow(m_WindowHandle);
		glClear(GL_COLOR_BUFFER_BIT);
		PollEvents();
	}

	void OpenGLWindow::PollEvents() {

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			//ImGui_ImplSDL3_ProcessEvent(&event);

			if (event.type == SDL_EVENT_QUIT) {
				m_shouldClose = true;
				g_SystemEventCallbacks.window_close_callback();
			}
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(m_WindowHandle)) {
				m_shouldClose = true;
				g_SystemEventCallbacks.window_close_callback();
			}

			switch (event.type) {
			case SDL_EventType::SDL_EVENT_WINDOW_RESIZED: {
				int32_t height, width;
				SDL_GetWindowSizeInPixels(m_WindowHandle, &height, &width);
				g_SystemEventCallbacks.framebuffer_size_callback(height, width);
				g_SystemEventCallbacks.window_size_callback(event.window.data1, event.window.data2);
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_MOVED: {
				g_SystemEventCallbacks.window_pos_callback(event.window.data1, event.window.data2);
			    break;
			}
			
			case SDL_EventType::SDL_EVENT_WINDOW_FOCUS_GAINED:
			case SDL_EventType::SDL_EVENT_WINDOW_FOCUS_LOST: {
				g_SystemEventCallbacks.window_focus_callback(event.type == SDL_EventType::SDL_EVENT_WINDOW_FOCUS_GAINED);
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_MAXIMIZED: {
				g_SystemEventCallbacks.window_maximize_callback();
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_MINIMIZED: {
				g_SystemEventCallbacks.window_minimize_callback();
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_EXPOSED: {
				g_SystemEventCallbacks.window_refresh_callback();
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_DISPLAY_CHANGED: {
				//g_SystemEventCallbacks.window_refresh_callback();
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED: {
				g_SystemEventCallbacks.window_content_scale_callback(event.window.data1, event.window.data2);
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_RESTORED: {
				g_SystemEventCallbacks.window_restore_callback();
				break;
			}

			}

		//--Sleep while minimized to reduce resource consumption (should not go here)
		//if (SDL_GetWindowFlags(m_WindowHandle) & SDL_WINDOW_MINIMIZED)
		//{
		//	SDL_Delay(10);
		//	continue;
		//}
		}
	}

	void OpenGLWindow::Shutdown()
	{
		//TODO check if this is the last sdl window open
		SDL_GL_DestroyContext(*m_OpenGLContext);
		SDL_DestroyWindow(m_WindowHandle);
		SDL_Quit();
	}

	bool OpenGLWindow::ShouldClose()
	{
		return m_shouldClose;
	}

	uint32_t OpenGLWindow::GetWidth()
	{
		return m_Width;
	}

	uint32_t OpenGLWindow::GetHeight()
	{
		return m_Height;
	}

	void* OpenGLWindow::getNativeHandle()
	{
		return m_WindowHandle;
	}

	void OpenGLWindow::SetCallbacks()
	{
		g_SystemEventCallbacks.framebuffer_size_callback = [](int width, int height) {
			glViewport(0, 0, width, height);
			FramebufferSizeEvent e = FramebufferSizeEvent(width, height);
			WindowEventsBus::Broadcast(&IWindowEvents::OnFramebufferSizeEvent, e);
	    };

		g_SystemEventCallbacks.window_close_callback = []() -> void {
			WindowCloseEvent e = WindowCloseEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowCloseEvent, e);
	    };

		g_SystemEventCallbacks.window_pos_callback = [](int xpos, int ypos) {
			WindowPositionEvent e = WindowPositionEvent(xpos, ypos);
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowPositionEvent, e);
	    };

		g_SystemEventCallbacks.window_size_callback = [](int width, int height) {
			WindowSizeEvent e = WindowSizeEvent(width, height);
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowSizeEvent, e);
	    };

		g_SystemEventCallbacks.window_content_scale_callback = [](float xscale, float yscale) {
			WindowContentScaleEvent e = WindowContentScaleEvent(xscale, yscale);
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowContentScaleEvent, e);
	    };

		g_SystemEventCallbacks.window_focus_callback = [](int focused) {
			WindowFocusEvent e = WindowFocusEvent(focused);
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowFocusEvent, e);
	    };

		g_SystemEventCallbacks.window_restore_callback = []() {
			WindowRestoreEvent e = WindowRestoreEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowRestoreEvent, e);
		};

		g_SystemEventCallbacks.window_minimize_callback = []() {
			WindowMinimizeEvent e = WindowMinimizeEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowMinimizeEvent, e);
	    };

		g_SystemEventCallbacks.window_maximize_callback = []() {
			WindowMaximizeEvent e = WindowMaximizeEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowMaximizeEvent, e);
	    };

		g_SystemEventCallbacks.window_refresh_callback = []() {
			WindowRefreshEvent e = WindowRefreshEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowRefreshEvent, e);
	    };
	}
}