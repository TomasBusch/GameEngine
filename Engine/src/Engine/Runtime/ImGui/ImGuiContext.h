#pragma once
#include "Engine/Core/Base.h"

#include "Platform/Window.h"

namespace Engine {
	class ImGuiContext {
	public:
		ImGuiContext() = default;
		virtual ~ImGuiContext() = default;

		virtual void Render() = 0;
		virtual void Init(const std::string& API_Version) = 0;

		static Scope<ImGuiContext> Create(Engine::Window* window);
	};
}