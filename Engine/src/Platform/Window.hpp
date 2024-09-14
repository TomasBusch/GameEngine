#pragma once
#include "pch.hpp"
#include "Engine/Core/Base.hpp"

#include "Engine/Core/Events/EventBus/EventBus.hpp"
#include "Engine/Core/Events/WindowEvents.hpp"

#include "Engine/RenderAPI/Context.hpp"
#include "Engine/RenderAPI/RenderAPI.hpp"

#include "Engine/Runtime/ImGui/ImGuiContext.hpp"

namespace Engine {

	struct IWindowEvents {
		virtual void OnFramebufferSizeEvent(FramebufferSizeEvent e) = 0;
		virtual void OnWindowCloseEvent(WindowCloseEvent e) = 0;
		virtual void OnWindowSizeEvent(WindowSizeEvent e) = 0;
		virtual void OnWindowContentScaleEvent(WindowContentScaleEvent e) = 0;
		virtual void OnWindowPositionEvent(WindowPositionEvent e) = 0;
		virtual void OnWindowRestoreEvent(WindowRestoreEvent e) = 0;
		virtual void OnWindowMinimizeEvent(WindowMinimizeEvent e) = 0;
		virtual void OnWindowMaximizeEvent(WindowMaximizeEvent e) = 0;
		virtual void OnWindowFocusEvent(WindowFocusEvent e) = 0;
		virtual void OnWindowRefreshEvent(WindowRefreshEvent e) = 0;
	};

	using WindowEventsBus = EventBus<IWindowEvents>;

	class WindowEventsListener : public WindowEventsBus::Handler {
	public:
		WindowEventsListener() {
			BusConnect();
		}
		~WindowEventsListener() {
			BusDisconnect();
		}

		//TODO Debug warning for unused events for all virtual functions
		virtual void OnFramebufferSizeEvent(FramebufferSizeEvent e) {};
		virtual void OnWindowCloseEvent(WindowCloseEvent e) {};
		virtual void OnWindowSizeEvent(WindowSizeEvent e) {};
		virtual void OnWindowContentScaleEvent(WindowContentScaleEvent e) {};
		virtual void OnWindowPositionEvent(WindowPositionEvent e) {};
		virtual void OnWindowRestoreEvent(WindowRestoreEvent e) {};
		virtual void OnWindowMinimizeEvent(WindowMinimizeEvent e) {};
		virtual void OnWindowMaximizeEvent(WindowMaximizeEvent e) {};
		virtual void OnWindowFocusEvent(WindowFocusEvent e) {};
		virtual void OnWindowRefreshEvent(WindowRefreshEvent e) {};
	};

	class Window {
	public:
		struct Params {
			std::uint32_t width = 640, height = 480;
			std::string Title = "Default Window (OpenGL)";
			Engine::RenderAPI::RenderAPITypes RenderAPI = Engine::RenderAPI::OPENGL;
		};

		Window(Params params) : m_RenderAPI(params.RenderAPI) {};
		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void InitImGui() = 0;
		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
		virtual bool ShouldClose() = 0;

		virtual void SetWindowGrabInput(bool grab) = 0;
		virtual void SetVsync(bool vsync) = 0;

		virtual std::uint32_t GetWidth() = 0;
		virtual std::uint32_t GetHeight() = 0;

		virtual ImGuiContext* ImGuiCtxInstance() = 0;

		virtual void* getNativeHandle() = 0;

		const Engine::RenderAPI::RenderAPITypes GetRenderAPIType() const { return m_RenderAPI; }

		static Scope<Window> Create(Params& params);
	private:
		Engine::RenderAPI::RenderAPITypes m_RenderAPI;
	protected:
		bool m_Vsync = false;
	};
}