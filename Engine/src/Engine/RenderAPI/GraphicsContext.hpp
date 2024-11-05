#pragma once

#include "RenderAPI.hpp"

namespace Engine {

	//Abstract class. All rendering api contexts must inherit from this class
	class Window;

	class GraphicsContext {
	public:
		GraphicsContext() {};
		virtual ~GraphicsContext() = default;

		virtual void Init(void* data_ptr) = 0;
		virtual void SetVsync(bool vsync) = 0;
	protected:
		mutable bool m_Vsync = false;

		friend Window;
	};

}
