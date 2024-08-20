#pragma once

#include "pch.hpp"

#include "Engine/Core/Base.hpp"

#include "Engine/Runtime/ImGui/ImGuiContext.hpp"
#include "Platform/Window.hpp"

namespace Engine {

	class ImGuiOpenGLContext : public ImGuiContext {
	public:
		ImGuiOpenGLContext(Window* window);
		~ImGuiOpenGLContext();

		virtual void Init(const std::string& glsl_version) override;
		virtual void Render() override;
	private:
		struct ImguiData; Scope<ImguiData> m_ImGuiData;
		Window* m_Window;
	};
}