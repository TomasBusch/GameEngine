#pragma once
#include "pch.h"
#include "Engine/Core/Base.h"

#include "Engine/RenderAPI/Context.h"
#include "Engine/RenderAPI/RenderAPI.h"

namespace Engine {

	class Window {
	public:
		struct Params {
			std::uint32_t width = 640, height = 480;
			std::string Title = "Default Window (OpenGL)";
			Engine::RenderAPI::RenderAPITypes RenderAPI = Engine::RenderAPI::OPENGL;
		};

	public:
		Window(Params params) : m_RenderAPI(params.RenderAPI) {};
		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
		virtual bool ShouldClose() = 0;

		virtual std::uint32_t GetWidth() = 0;
		virtual std::uint32_t GetHeight() = 0;

		virtual void* getNativeHandle() = 0;

		const Engine::RenderAPI::RenderAPITypes GetRenderAPIType() const { return m_RenderAPI; }

		static Scope<Window> Create(Params& params);
	private:
		Engine::RenderAPI::RenderAPITypes m_RenderAPI;
	};
}