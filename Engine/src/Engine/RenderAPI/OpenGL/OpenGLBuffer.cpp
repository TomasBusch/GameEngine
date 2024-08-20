#include "OpenGLBuffer.hpp"

#include <glad/gl.h>

namespace Engine::RenderAPI {

	OpenGLBuffer::OpenGLBuffer()
	{
		glCreateBuffers(1, &m_RenderID);
	}

	OpenGLBuffer::~OpenGLBuffer() {
		glDeleteBuffers(1, &m_RenderID);
	}

	void OpenGLBuffer::Bind()
	{
		glBindBuffer();
	}

	void OpenGLBuffer::UnBind()
	{

	}

}
