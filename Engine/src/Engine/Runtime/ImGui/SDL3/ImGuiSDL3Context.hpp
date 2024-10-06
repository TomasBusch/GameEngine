#pragma once

#include "pch.hpp"

#include "Engine/Core/Base.hpp"

#include <SDL2/SDL.h>

#include "Platform/Window.hpp"
#include "Engine/Runtime/ImGui/ImGuiContext.hpp"


namespace Engine {

	class ImGuiSDL3Context : public ImGuiContext {
	public:
		ImGuiSDL3Context();
		~ImGuiSDL3Context();

		virtual void Init(void* platform_data) override;
		virtual void BeginFrame() override;
		virtual void EndFrame() override;
		//virtual void Render(Callback<> cb) override;

		constexpr static ContextType GetClassContextType() {
			return ContextType::GLFW;
		};

		struct PlatformData {
			SDL_Window* m_WindowHandle;
			SDL_GLContextState* m_Context;
		};
	private:
		struct ImguiData; Scope<ImguiData> m_ImGuiData;
	};
}