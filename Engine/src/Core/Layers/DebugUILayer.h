#pragma once

#include "Layer.h"

namespace Engine {
	class DebugUILayer : public Layer {
	public:
		virtual void onUpdate(Timestep ts) override;
	private:

	};
}