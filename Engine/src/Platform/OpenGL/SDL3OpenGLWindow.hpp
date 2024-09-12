#pragma once

#include "Platform/Window.hpp"
#include "Engine/Runtime/ImGui/SDL3/ImGuiSDL3Context.hpp"

#include <SDL3/SDL.h>

namespace Engine {
	class SDL3OpenGLWindow : public Window {
	public:
		SDL3OpenGLWindow() = delete;
		SDL3OpenGLWindow(Window::Params& params);
		virtual ~SDL3OpenGLWindow();

		virtual void Init() override;
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
	};
}