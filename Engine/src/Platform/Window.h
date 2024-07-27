#pragma once
#include "pch.h"

#include "RenderAPI/Context.h"
#include "Core/Definitions/Memory.h"

namespace Engine {
	struct WindowParams {
		std::uint32_t width, height;
		std::string Title;
	};

	class Window {
	public:

		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
		virtual bool ShouldClose() = 0;

		virtual std::uint32_t GetWidth() = 0;
		virtual std::uint32_t GetHeight() = 0;

		static Scope<Window> Create(WindowParams& params);
	private:
	};
}