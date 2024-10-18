#pragma once

#include "pch.hpp"

#include "Engine/Core/Base.hpp"

#include <glfw/glfw3.h>

#include "Engine/Runtime/Window.hpp"
#include "Engine/ImGui/ImGuiContext.hpp"

namespace Engine {

	class ImGuiOpenGLContext : public ImGuiContext {
	public:
		ImGuiOpenGLContext(Window* window);
		~ImGuiOpenGLContext();

		virtual void Init() override;
		virtual void BeginFrame() override;
		virtual void EndFrame() override;
	protected:
		WindowAPI m_WindowAPI = WindowAPI::GLFW_API;
		RenderAPI m_RenderAPI = RenderAPI::OPENGL;
	};
}