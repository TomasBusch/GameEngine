#pragma once

#include "Engine/Core/Time/Timestamp.hpp"

namespace Engine {

	class Event {
	public:
		enum Priority
		{
			REAL_TIME = 4,
			HIGH = 3,
			MEDIUM = 2,
			LOW = 1
		};
	public:
		Event() = default;
		Event(Priority priority)
			:m_Priority(priority)
		{}
		Timestamp GetTimestamp() { return m_Timestamp; }

		friend bool operator<(const Event& l, const Event& r) {
			return (l.m_Priority < r.m_Priority);
		}
		friend bool operator>(const Event& l, const Event& r) {
			return (r < l);
		}
		friend bool operator<=(const Event& l, const Event& r) {
			return !(l > r);
		}
		friend bool operator>=(const Event& l, const Event& r) {
			return !(l < r);
		}
	public:
		Priority m_Priority = LOW;
	private:
		Timestamp m_Timestamp = Timestamp();
	};
}