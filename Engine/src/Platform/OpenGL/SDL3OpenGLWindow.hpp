#pragma once

#include "Platform/Window.hpp"
#include <SDL3/SDL.h>

namespace Engine {
	class OpenGLWindow : public Window {
	public:
		OpenGLWindow() = delete;
		OpenGLWindow(Window::Params& params);
		virtual ~OpenGLWindow();

		virtual void Init() override;
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		virtual bool ShouldClose() override;

		virtual std::uint32_t GetWidth() override;
		virtual std::uint32_t GetHeight() override;

		virtual void* getNativeHandle() override;
	private:
		void SetCallbacks();
		void PollEvents();
	private:
		SDL_Window* m_WindowHandle;
		SDL_GLContext* m_OpenGLContext;

		std::uint32_t m_Width, m_Height;

		bool m_shouldClose = false;
	};
}