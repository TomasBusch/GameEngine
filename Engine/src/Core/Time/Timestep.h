#pragma once

#include "pch.h"

namespace Engine {

	namespace Units {
		using ns = std::chrono::nanoseconds;
		using ms = std::chrono::milliseconds;
		using sec = std::chrono::seconds;
	}

	class Timestep {
	public:
		Timestep(const Units::ns& duration)
			:m_Duration(duration)
		{}

		operator float() const { std::chrono::duration_cast<Units::ms>(m_Duration).count() / 1000; };
	private:
		Units::ns m_Duration;
	};
}