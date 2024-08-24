#include "OpenGLVertexArray.hpp"

#include <GLFW/glfw3.h>
#include <glad/gl.h>

namespace Engine::RenderAPI {

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RenderID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::BindBuffer(OpenGLBuffer& vbo, VertexAttribLayout& layout)
	{

	}

}

