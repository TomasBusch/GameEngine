#pragma once

#include "Event.hpp"
#include "Platform/Input.hpp"

#include <glm/glm.hpp>

namespace Engine::Input {
	
	class KeyEvent : public Event {
	public:
		KeyCode Key;
		KeyAction Action;
		KeyModifiers Modifiers;
	public:
		KeyEvent(KeyCode kc, KeyAction action, KeyModifiers mod)
			:Key(kc), Action(action), Modifiers(mod), Event(Event::Priority::REAL_TIME)
		{}
		KeyEvent(KeyCode kc, KeyAction action, KeyModifiers mod, Event::Priority priority)
			:Key(kc), Action(action), Modifiers(mod), Event(priority)
		{}
	};

	class TextEvent : public Event {
	public:
		uint64_t UnicodeCode;
	public:
		TextEvent(uint64_t uc)
			:UnicodeCode(uc), Event(Event::Priority::LOW)
		{}
		TextEvent(uint64_t uc, Event::Priority priority)
			:UnicodeCode(uc), Event(priority)
		{}
	};

	class MouseButtonEvent : public Event {
	public:
		MouseButtonCode Button;
		KeyAction Action;
	public:
		MouseButtonEvent(MouseButtonCode bc, KeyAction action)
			:Button(bc), Action(action), Event(Event::Priority::REAL_TIME)
		{}
		MouseButtonEvent(MouseButtonCode bc, KeyAction action, Event::Priority priority)
			:Button(bc), Action(action), Event(priority)
		{}
	};

	class MouseMoveEvent : public Event {
	public:
		glm::vec2 Position;
		glm::vec2 Movement;
	public:
		MouseMoveEvent(glm::vec2 pos, glm::vec2 move)
			:Position(pos), Movement(move), Event(Event::Priority::REAL_TIME)
		{}
		MouseMoveEvent(glm::vec2 pos, glm::vec2 move, Event::Priority priority)
			:Position(pos), Movement(move), Event(priority)
		{}
	};

	class MouseEnterEvent : public Event {
	public:
		MouseEnterEvent()
			:Event(Event::Priority::REAL_TIME)
		{}
		MouseEnterEvent(Event::Priority priority)
			:Event(priority)
		{}
	};


	class MouseLeaveEvent : public Event {
	public:
		MouseLeaveEvent()
			:Event(Event::Priority::REAL_TIME)
		{}
		MouseLeaveEvent( Event::Priority priority)
			:Event(priority)
		{}
	};

	class MouseScrollEvent : public Event {
	public:
		glm::vec2 Offset;
	public:
		MouseScrollEvent(glm::vec2 offset)
			:Offset(offset), Event(Event::Priority::REAL_TIME)
		{}
		MouseScrollEvent(glm::vec2 offset, Event::Priority priority)
			:Offset(offset), Event(priority)
		{}
	};
}