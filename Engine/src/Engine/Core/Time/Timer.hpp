#pragma once
#include "pch.hpp"

#include "Timestep.hpp"

namespace Engine {

	class Timer {
	public:
		Timer();

		void Reset();

		Timestep Elapsed();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};

}