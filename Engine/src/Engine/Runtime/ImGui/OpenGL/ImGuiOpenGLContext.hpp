#pragma once

#include "pch.hpp"

#include "Engine/Core/Base.hpp"

#include "Platform/Window.hpp"
#include "Engine/Runtime/ImGui/ImGuiContext.hpp"

namespace Engine {

	class ImGuiOpenGLContext : public ImGuiContext {
	public:
		ImGuiOpenGLContext(Window* window);
		~ImGuiOpenGLContext();

		virtual void Init(const std::string& glsl_version) override;
		virtual void BeginFrame() override;
		virtual void EndFrame() override;
		//virtual void Render(Callback<> cb) override;
	private:
		struct ImguiData; Scope<ImguiData> m_ImGuiData;
		Window* m_Window;
	};
}