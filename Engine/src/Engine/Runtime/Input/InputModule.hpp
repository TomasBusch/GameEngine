#pragma once
#include "pch.hpp"
#include "Engine/Core/Base.hpp"

#include "Platform/Window.hpp"

#include "Engine/Core/Events/EventBus/EventBus.hpp"
#include "Engine/Core/Events/InputEvents.hpp"

namespace Engine::Input {

	struct IKeyboardEvents{
		virtual void OnKeyEvent(KeyEvent e) = 0;
		virtual void OnTextEvent(TextEvent e) = 0;
	};

	struct IMouseEvents {
		virtual void OnMouseEnterEvent(MouseEnterEvent e) = 0;
		virtual void OnMouseLeaveEvent(MouseLeaveEvent e) = 0;
		virtual void OnMouseMoveEvent(MouseMoveEvent e) = 0;
		virtual void OnMouseButtonEvent(MouseButtonEvent e) = 0;
		virtual void OnMouseScrollEvent(MouseScrollEvent e) = 0;
	};

	using KeyboardEventsBus = EventBus<IKeyboardEvents>;
	using MouseEventsBus = EventBus<IMouseEvents>;

	class KeyboardEventsListener : public KeyboardEventsBus::Handler {
	public:
		KeyboardEventsListener() {
			BusConnect();
		}
		~KeyboardEventsListener() {
			BusDisconnect();
		}

		//TODO Debug warning for unused events for all virtual functions
		virtual void OnKeyEvent(KeyEvent e) override {};
		virtual void OnTextEvent(TextEvent e) override {};
	};

	class MouseEventsListener : public MouseEventsBus::Handler {
	public:
		MouseEventsListener() {
			BusConnect();
		}
		~MouseEventsListener() {
			BusDisconnect();
		}

		virtual void OnMouseEnterEvent(MouseEnterEvent e) override {};
		virtual void OnMouseLeaveEvent(MouseLeaveEvent e) override {};
		virtual void OnMouseMoveEvent(MouseMoveEvent e) override {};
		virtual void OnMouseButtonEvent(MouseButtonEvent e) override {};
		virtual void OnMouseScrollEvent(MouseScrollEvent e) override {};
	};

	class InputModule {
	public:
		InputModule(InputModule& other) = delete;
		void operator=(const InputModule&) = delete;

		static InputModule* GetInstance();

		void Init(Window* window);

//		Ref<Publisher<KeyboardEvent>> GetKeyPublisher() { return m_KeyboardInputPub; };

	protected:
		InputModule() {};
		~InputModule() = default;
	private:
		static InputModule* g_Instance;
		static std::mutex s_Mutex;
		static bool m_Initialized;

//		Ref<Publisher<KeyboardEvent>> m_KeyboardInputPub;
	};
}