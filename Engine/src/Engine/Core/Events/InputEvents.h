#pragma once

#include "Event.h"

namespace Engine {
	class KeyboardEvent : public Event {
	public:
		std::string KEYCODE;
	public:
		KeyboardEvent(const std::string& kc)
			:KEYCODE(kc), Event(Event::Priority::REAL_TIME)
		{}
		KeyboardEvent(const std::string& kc, Event::Priority priority)
			:KEYCODE(kc), Event(priority)
		{}
	};
}