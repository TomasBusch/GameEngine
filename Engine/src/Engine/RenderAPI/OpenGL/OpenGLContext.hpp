#pragma once

#include "Engine/RenderAPI/RenderContext.hpp"

namespace Engine {
	class OpenGLContext : public RenderContext {
	public:
		OpenGLContext();
		virtual ~OpenGLContext();

		void Init(void* data_ptr) override;
		void SetVsync(bool vsync) override;
	public:
		RenderAPI m_RenderAPI = RenderAPI::OPENGL;
	};
}
