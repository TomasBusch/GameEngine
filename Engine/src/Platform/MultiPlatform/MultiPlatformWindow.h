/*
#pragma once

#include "Platform/Window.h"
#include <GLFW/glfw3.h>

namespace Engine {
	class MultiplatformWindow : public Window {
		MultiplatformWindow();
		virtual ~MultiplatformWindow();

		virtual void Init() override;
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		virtual bool ShouldClose() override;

		GLFWwindow* GetNativeHandle();
	private:
		Scope<Context> m_Context;

		GLFWwindow* m_WindowHandle;
	};
}
*/