#pragma once

#include "pch.hpp"

#include "Engine/Core/Base.hpp"

#include <glfw/glfw3.h>

#include "Platform/Window.hpp"
#include "Engine/Runtime/ImGui/ImGuiContext.hpp"

namespace Engine {

	class ImGuiGLFWContext : public ImGuiContext {
	public:
		ImGuiGLFWContext();
		~ImGuiGLFWContext();

		virtual void Init(void* platform_data) override;
		virtual void BeginFrame() override;
		virtual void EndFrame() override;
		//virtual void Render(Callback<> cb) override;

		constexpr static ContextType GetClassContextType() {
			return ContextType::GLFW;
		};

		struct PlatformData {
			GLFWwindow* m_WindowHandle;
		};
	private:
		struct ImguiData; Scope<ImguiData> m_ImGuiData;
	};
}