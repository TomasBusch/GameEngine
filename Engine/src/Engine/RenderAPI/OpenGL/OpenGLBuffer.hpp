#pragma once

#include "Engine/RenderAPI/Buffer.hpp"

namespace Engine::RenderAPI {
	class OpenGLBuffer : public Buffer {
	public:
		OpenGLBuffer();
		~OpenGLBuffer();

		virtual void Bind() override;
		virtual void UnBind() override;
	private:
		uint32_t m_RenderID;
	};
}