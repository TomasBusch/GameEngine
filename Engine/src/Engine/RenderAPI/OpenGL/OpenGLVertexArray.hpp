#pragma once
#include "pch.hpp"

#include "Engine/RenderAPI/VertexArray.hpp"

namespace Engine::RenderAPI {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();
	private:
		glm::uint32 m_RenderID;
	};
}