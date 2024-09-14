#pragma once

#include "Platform/Window.hpp"
#include "Engine/Runtime/ImGui/SDL3/ImGuiSDL3Context.hpp"

#include <SDL3/SDL.h>

namespace Engine {
	class SDL3OpenGLWindow : public Window {
	public:
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

		SDL3OpenGLWindow() = delete;
		SDL3OpenGLWindow(Window::Params& params);
		virtual ~SDL3OpenGLWindow();

		virtual void Init() override;
		virtual void InitImGui() override;
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		virtual bool ShouldClose() override;

		virtual std::uint32_t GetWidth() override;
		virtual std::uint32_t GetHeight() override;

		virtual ImGuiContext* ImGuiCtxInstance() override;

		virtual void SetWindowGrabInput(bool grab) override;
		virtual void SetVsync(bool vsync) override;

		virtual void* getNativeHandle() override;
	private:
		void SetCallbacks();
		void PollEvents();
	private:
		SDL_Window* m_WindowHandle;
		SDL_GLContextState* m_OpenGLContext;
		ImGuiSDL3Context* m_ImGuiContext;

		std::uint32_t m_Width, m_Height;
		bool m_shouldClose = false;

		SystemEventsCallbacks m_SysCallbacks;

	};
}