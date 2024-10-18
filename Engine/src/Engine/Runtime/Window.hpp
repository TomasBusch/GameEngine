#pragma once
#include "pch.hpp"
#include "Engine/Core/Base.hpp"

#include "Engine/Events/EventBus/EventBus.hpp"
#include "Engine/Events/WindowEvents.hpp"

#include "Engine/RenderAPI/RenderAPI.hpp"
#include "Engine/RenderAPI/RenderContext.hpp"

namespace Engine {

	//Events
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
	//End Events

	enum class WindowAPI {
		NONE,
		GLFW_API,
		SDL2_API,
		SDL3_API,
	};

	class Window {
	public:
		struct Params {
			std::uint32_t width = 640, height = 480;
			std::string title = "Default Window (OpenGL)";
			RenderAPI renderAPI;
		};


		Window(Params params) : m_Width(params.width), m_Height(params.height), m_Title(params.title) {};
		virtual ~Window() = default;

		virtual void Init() = 0;
		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
		virtual bool ShouldClose() = 0;

		virtual void SetWindowGrabInput(bool grab) = 0;

		inline const std::uint32_t GetWidth()  const { return m_Width;  };
		inline const std::uint32_t GetHeight() const { return m_Height; };

		virtual void* getNativeHandle() = 0;

		static Scope<Window> Create(Params& params);
	protected:
		std::uint32_t m_Width, m_Height;
		std::string m_Title;

		void* m_PlatformData = nullptr;

		bool m_Vsync = false;
	};
}