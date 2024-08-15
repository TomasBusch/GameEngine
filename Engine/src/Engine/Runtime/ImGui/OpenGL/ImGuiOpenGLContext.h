#pragma once

#include "pch.h"

#include "Engine/Core/Base.h"

#include "Engine/Runtime/ImGui/ImGuiContext.h"
#include "Platform/Window.h"

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