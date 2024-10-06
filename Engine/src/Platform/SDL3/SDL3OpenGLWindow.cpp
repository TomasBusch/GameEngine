#include "SDL3OpenGLWindow.hpp"


#include <glad/gl.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

#include <backends/imgui_impl_sdl3.h>

namespace Engine {

	SDL3OpenGLWindow::SDL3OpenGLWindow(Window::Params& params)
		:m_Width(params.width), m_Height(params.height), m_WindowHandle(nullptr), m_OpenGLContext(nullptr), m_ImGuiContext(nullptr), Window(params)
	{

	}

	SDL3OpenGLWindow::~SDL3OpenGLWindow()
	{
		Shutdown();
	}

	void SDL3OpenGLWindow::Init()
	{

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_EVENTS) < 0)
		{
			ENGINE_CORE_BREAK(SDL_GetError());
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
		m_OpenGLContext = SDL_GL_CreateContext(m_WindowHandle);
		SDL_GL_MakeCurrent(m_WindowHandle, m_OpenGLContext);
		SDL_ShowWindow(m_WindowHandle);

		gladLoadGL(SDL_GL_GetProcAddress);

		SetCallbacks();

		m_ImGuiContext = (ImGuiSDL3Context*)ImGuiContext::Create<ImGuiSDL3Context>();

	}

	void SDL3OpenGLWindow::InitImGui()
	{
		ImGuiSDL3Context::PlatformData data;
		data.m_WindowHandle = m_WindowHandle;
		data.m_Context = m_OpenGLContext;
		m_ImGuiContext->Init(&data);
	}

	void SDL3OpenGLWindow::OnUpdate()
	{
		SDL_GL_SwapWindow(m_WindowHandle);
		glClear(GL_COLOR_BUFFER_BIT);
		PollEvents();
	}

	void SDL3OpenGLWindow::PollEvents() {

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL3_ProcessEvent(&event);

			if (event.type == SDL_EVENT_QUIT) {
				m_shouldClose = true;
				m_SysCallbacks.window_close_callback();
			}
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(m_WindowHandle)) {
				m_shouldClose = true;
				m_SysCallbacks.window_close_callback();
			}

			switch (event.type) {
			case SDL_EventType::SDL_EVENT_WINDOW_RESIZED: {
				int32_t height, width;
				SDL_GetWindowSizeInPixels(m_WindowHandle, &height, &width);
				m_SysCallbacks.framebuffer_size_callback(height, width);
				m_SysCallbacks.window_size_callback(event.window.data1, event.window.data2);
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_MOVED: {
				m_SysCallbacks.window_pos_callback(event.window.data1, event.window.data2);
			    break;
			}
			
			case SDL_EventType::SDL_EVENT_WINDOW_FOCUS_GAINED:
			case SDL_EventType::SDL_EVENT_WINDOW_FOCUS_LOST: {
				m_SysCallbacks.window_focus_callback(event.type == SDL_EventType::SDL_EVENT_WINDOW_FOCUS_GAINED);
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_MAXIMIZED: {
				m_SysCallbacks.window_maximize_callback();
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_MINIMIZED: {
				m_SysCallbacks.window_minimize_callback();
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_EXPOSED: {
				m_SysCallbacks.window_refresh_callback();
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_DISPLAY_CHANGED: {
				//m_SysCallbacks.window_refresh_callback();
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED: {
				m_SysCallbacks.window_content_scale_callback(event.window.data1, event.window.data2);
				break;
			}

			case SDL_EventType::SDL_EVENT_WINDOW_RESTORED: {
				m_SysCallbacks.window_restore_callback();
				break;
			}

			default: {
				//Return unhandled events to the queue
				// ERROR: Causes infinite loop with imgui
				//SDL_PushEvent(&event);
			}

			}
		}
	}

	void SDL3OpenGLWindow::Shutdown()
	{
		//TODO check if this is the last sdl window open
		SDL_GL_DestroyContext(m_OpenGLContext);
		SDL_DestroyWindow(m_WindowHandle);
		SDL_Quit();
	}

	bool SDL3OpenGLWindow::ShouldClose()
	{
		return m_shouldClose;
	}

	uint32_t SDL3OpenGLWindow::GetWidth()
	{
		return m_Width;
	}

	uint32_t SDL3OpenGLWindow::GetHeight()
	{
		return m_Height;
	}

	ImGuiContext* SDL3OpenGLWindow::ImGuiCtxInstance()
	{
		return m_ImGuiContext;
	}

	void* SDL3OpenGLWindow::getNativeHandle()
	{
		return m_WindowHandle;
	}

	void SDL3OpenGLWindow::SetCallbacks()
	{
		m_SysCallbacks.framebuffer_size_callback = [](int width, int height) {
			glViewport(0, 0, width, height);
			FramebufferSizeEvent e = FramebufferSizeEvent(width, height);
			WindowEventsBus::Broadcast(&IWindowEvents::OnFramebufferSizeEvent, e);
	    };

		m_SysCallbacks.window_close_callback = []() -> void {
			WindowCloseEvent e = WindowCloseEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowCloseEvent, e);
	    };

		m_SysCallbacks.window_pos_callback = [](int xpos, int ypos) {
			WindowPositionEvent e = WindowPositionEvent(xpos, ypos);
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowPositionEvent, e);
	    };

		m_SysCallbacks.window_size_callback = [](int width, int height) {
			WindowSizeEvent e = WindowSizeEvent(width, height);
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowSizeEvent, e);
	    };

		m_SysCallbacks.window_content_scale_callback = [](float xscale, float yscale) {
			WindowContentScaleEvent e = WindowContentScaleEvent(xscale, yscale);
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowContentScaleEvent, e);
	    };

		m_SysCallbacks.window_focus_callback = [](int focused) {
			WindowFocusEvent e = WindowFocusEvent(focused);
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowFocusEvent, e);
	    };

		m_SysCallbacks.window_restore_callback = []() {
			WindowRestoreEvent e = WindowRestoreEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowRestoreEvent, e);
		};

		m_SysCallbacks.window_minimize_callback = []() {
			WindowMinimizeEvent e = WindowMinimizeEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowMinimizeEvent, e);
	    };

		m_SysCallbacks.window_maximize_callback = []() {
			WindowMaximizeEvent e = WindowMaximizeEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowMaximizeEvent, e);
	    };

		m_SysCallbacks.window_refresh_callback = []() {
			WindowRefreshEvent e = WindowRefreshEvent();
			WindowEventsBus::Broadcast(&IWindowEvents::OnWindowRefreshEvent, e);
	    };
	}

	void SDL3OpenGLWindow::SetWindowGrabInput(bool grab)
	{
		SDL_SetWindowKeyboardGrab(m_WindowHandle, grab);
		SDL_SetWindowMouseGrab(m_WindowHandle, grab);
	}

	void SDL3OpenGLWindow::SetVsync(bool vsync)
	{
		SDL_GL_SetSwapInterval(vsync);
		m_Vsync = vsync;
	}
}