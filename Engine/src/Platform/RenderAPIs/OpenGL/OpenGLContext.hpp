#pragma once

#include "Engine/RenderAPI/GraphicsContext.hpp"

namespace Engine {

	class OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext();
		virtual ~OpenGLContext();

		void Init(void* data_ptr) override;
		void SetVsync(bool vsync) override;

	};
}