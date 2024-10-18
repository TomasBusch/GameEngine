#pragma once

#include "RenderAPI.hpp"


namespace Engine {

	//Abstract class. All rendering api contexts must inherit from this class
	class Window;

	class RenderContext {
	public:
		RenderContext() {};
		virtual ~RenderContext() = default;

		virtual void Init(void* data_ptr) = 0;
		virtual void SetVsync(bool vsync) = 0;

	public:
		RenderAPI m_RenderAPI = RenderAPI::NONE;
	protected:
		mutable bool m_Vsync = false;

		friend Window;
	};

}
