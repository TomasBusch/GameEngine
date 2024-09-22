#pragma once
#include "pch.hpp"

#include "OpenGLBuffer.hpp"

namespace Engine::RenderAPI {

	enum class VertexDataType : std::uint8_t {
		BYTE,
		U_BYTE,
		SHORT,
		U_SHORT,
		INT,
		U_INT,
		HALF_FLOAT,
		FLOAT,
		DOUBLE,
		FIXED
	};

	struct VertexAttribLayoutElement {
		VertexDataType type;
		std::size_t offset;
		std::uint8_t count;
		std::byte normalized;

		VertexAttribLayoutElement(VertexDataType t, std::uint32_t c, std::size_t s, std::byte n, std::size_t o)
			:type(t), count(c), normalized(n), offset(o)
		{}
	};

	struct VertexAttribLayout {
		std::vector<VertexAttribLayoutElement> elements;
		std::size_t stride;

		VertexAttribLayout(std::vector<VertexAttribLayoutElement> e, std::size_t s)
			:elements(e), stride(s)
		{}
	};

	class OpenGLVertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind();
		void Unbind();
		void BindVertexBuffer(OpenGLBuffer& vertexBuffer, VertexAttribLayout& vertexLayout);
	private:
		glm::uint32 m_RenderID;
	};
}