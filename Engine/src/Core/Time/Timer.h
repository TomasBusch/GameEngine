#pragma once

#include "pch.h"

#include "Timestep.h"

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