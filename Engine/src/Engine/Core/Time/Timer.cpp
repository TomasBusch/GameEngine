#include "Timer.hpp"

namespace Engine {

	void Timer::Reset()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	Timestep Timer::Elapsed() {
		return (std::chrono::high_resolution_clock::now() - m_Start);
	}
}