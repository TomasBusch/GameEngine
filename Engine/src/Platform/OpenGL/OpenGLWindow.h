#pragma once

#include "Platform/Window.h"
#include <GLFW/glfw3.h>

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
		GLFWwindow* m_WindowHandle;

		std::uint32_t m_Width, m_Height;
	};
}