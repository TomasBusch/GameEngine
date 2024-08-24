#pragma once
#include "Engine/Core/Base.hpp"

#include "Platform/Window.hpp"

#include <imgui.h>

namespace Engine {
	class ImGuiContext {
	public:
		ImGuiContext() = default;
		virtual ~ImGuiContext() = default;

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
		//virtual void Render(Callback<> cb) = 0;
		virtual void Init(const std::string& API_Version) = 0;

		static Scope<ImGuiContext> Create(Engine::Window* window);
	};
}