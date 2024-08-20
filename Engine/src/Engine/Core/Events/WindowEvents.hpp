#pragma once
#include "pch.hpp"

#include "Event.hpp"

#include <glm/glm.hpp>

namespace Engine {
	
	class FramebufferSizeEvent : public Event {
	public:
		uint32_t Width = 0;
		uint32_t Height = 0;
	public:
		FramebufferSizeEvent(uint32_t w, uint32_t h)
			:Width(w), Height(h), Event(Event::Priority::REAL_TIME)
		{}
		FramebufferSizeEvent(uint32_t w, uint32_t h, Event::Priority priority)
			:Width(w), Height(h), Event(priority)
		{}
	};
	
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent()
			:Event(Event::Priority::REAL_TIME)
		{}
		WindowCloseEvent(Event::Priority priority)
			:Event(priority)
		{}
	};

	class WindowSizeEvent : public Event {
	public:
		glm::int32 Width;
		glm::int32 Height;
	public:
		WindowSizeEvent(glm::int32 w, glm::int32 h)
			:Width(w), Height(h), Event(Event::Priority::REAL_TIME)
		{}
		WindowSizeEvent(glm::int32 w, glm::int32 h, Event::Priority priority)
			:Width(w), Height(h), Event(priority)
		{}
	};

	class WindowContentScaleEvent : public Event {
	public:
		glm::f32 XScale;
		glm::f32 YScale;
	public:
		WindowContentScaleEvent(glm::f32 xscale, glm::f32 yscale)
			:XScale(xscale), YScale(yscale), Event(Event::Priority::REAL_TIME)
		{}
		WindowContentScaleEvent(glm::f32 xscale, glm::f32 yscale, Event::Priority priority)
			:XScale(xscale), YScale(yscale), Event(priority)
		{}
	};

	class WindowPositionEvent : public Event {
	public:
		glm::int32 XPos;
		glm::f32 YPos;
	public:
		WindowPositionEvent(glm::f32 xpos, glm::f32 ypos)
			:XPos(xpos), YPos(ypos), Event(Event::Priority::REAL_TIME)
		{}
		WindowPositionEvent(glm::f32 xpos, glm::f32 ypos, Event::Priority priority)
			:XPos(xpos), YPos(ypos), Event(priority)
		{}
	};

	class WindowIconifyEvent : public Event {
	public:
		bool Iconified;
	public:
		WindowIconifyEvent(bool iconified)
			:Iconified(iconified), Event(Event::Priority::REAL_TIME)
		{}
		WindowIconifyEvent(bool iconified, Event::Priority priority)
			:Iconified(iconified), Event(priority)
		{}
	};

	class WindowMaximizeEvent : public Event {
	public:
		bool Maximized;
	public:
		WindowMaximizeEvent(bool maximized)
			:Maximized(maximized), Event(Event::Priority::REAL_TIME)
		{}
		WindowMaximizeEvent(bool maximized, Event::Priority priority)
			:Maximized(maximized), Event(priority)
		{}
	};

	class WindowFocusEvent : public Event {
	public:
		bool Focused;
	public:
		WindowFocusEvent(bool focused)
			:Focused(focused), Event(Event::Priority::REAL_TIME)
		{}
		WindowFocusEvent(bool focused, Event::Priority priority)
			:Focused(focused), Event(priority)
		{}
	};

	class WindowRefreshEvent : public Event {
	public:
		WindowRefreshEvent()
			:Event(Event::Priority::REAL_TIME)
		{}
		WindowRefreshEvent(Event::Priority priority)
			:Event(priority)
		{}
	};
}