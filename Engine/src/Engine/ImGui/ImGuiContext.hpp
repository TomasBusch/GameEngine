#pragma once
#include "Engine/Core/Base.hpp"

#include "Engine/RenderAPI/RenderAPI.hpp"
#include "Engine/Runtime/Window.hpp"

#include <imgui.h>

namespace Engine {

	class ImGuiContext {
	public:
		struct ImGuiContextData {
			ImGuiIO* io;
			ImGuiStyle* style;
		};

		ImGuiContext(Window* window) :m_Window(window) {};
		virtual ~ImGuiContext() = default;

		virtual void Init() = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		static Scope<ImGuiContext> Create(Window* window);

	protected:
		Window* m_Window;
		ImGuiContextData m_ContextData = ImGuiContextData();

		WindowAPI m_WindowAPI = WindowAPI::NONE;
		RenderAPI::API m_RenderAPI = RenderAPI::API::NONE;
	};
}