#pragma once

#include "Platform/Window.hpp"
#include <GLFW/glfw3.h>

#include "Engine/Runtime/ImGui/GLFW/ImGuiGLFWContext.hpp"

namespace Engine {
	class GLFWOpenGLWindow : public Window {
	public:
		GLFWOpenGLWindow() = delete;
		GLFWOpenGLWindow(Window::Params& params);
		virtual ~GLFWOpenGLWindow();

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
	private:
		GLFWwindow* m_WindowHandle;

		ImGuiGLFWContext* m_ImGuiContext;

		std::uint32_t m_Width, m_Height;
	};
}