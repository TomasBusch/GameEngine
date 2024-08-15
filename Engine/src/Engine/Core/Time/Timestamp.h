#pragma once
#include "pch.h"

namespace Engine {
	class Timestamp {
	public:
		Timestamp()
			:m_Timestamp(std::chrono::high_resolution_clock::now())
		{}

		Timestamp(std::chrono::high_resolution_clock::time_point ts)
			:m_Timestamp(ts)
		{}

		friend std::ostream& operator<<(std::ostream& os, const Timestamp& object) {
			os << object.m_Timestamp.time_since_epoch();
			return os;
		}
	private:
		std::chrono::high_resolution_clock::time_point m_Timestamp;
	};
}
