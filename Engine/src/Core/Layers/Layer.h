#pragma once

#include "Core/Time/Timestep.h"

namespace Engine {
	class Layer {
	public:
		virtual void onUpdate(Timestep ts) = 0;
	private:

	};
}