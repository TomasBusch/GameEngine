#pragma once

#include "Engine/RenderAPI/VertexBuffer.hpp"

namespace Engine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer() = default;
		~OpenGLVertexBuffer() = default;
	};
}