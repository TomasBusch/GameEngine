#include "OpenGLVertexArray.hpp"

#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace Engine::RenderAPI {

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RenderID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::BindVertexBuffer(OpenGLBuffer& vertexBuffer, VertexAttribLayout& vertexLayout)
	{
		Bind();
		vertexBuffer.Bind();
	}

}

