#include "Engine/Core/Base.hpp"

#include "OpenGLBuffer.hpp"

#include <glad/gl.h>

namespace Engine::RenderAPI {

	void OpenGLBuffer::Copy(OpenGLBuffer& readbuffer, OpenGLBuffer& writebuffer)
	{
		ENGINE_CORE_ASSERT(readbuffer.m_Size <= writebuffer.m_Size, "ERROR: Cannot copy contents of one buffer into a smaller buffer");

		glCopyNamedBufferSubData(readbuffer.m_RenderID, writebuffer.m_RenderID, 0, 0, readbuffer.m_Size);
	}

	void OpenGLBuffer::Copy(OpenGLBuffer& readbuffer, OpenGLBuffer& writebuffer, std::uintptr_t readoffset, std::uintptr_t writeoffset, std::size_t size)
	{
		ENGINE_CORE_ASSERT(readbuffer.m_Size <= (readoffset + size), "ERROR: Cannot copy from outside the buffer's memory");
		ENGINE_CORE_ASSERT(writebuffer.m_Size <= (writeoffset + size), "ERROR: Write buffer does not have enough memory to copy into");

		glCopyNamedBufferSubData(readbuffer.m_RenderID, writebuffer.m_RenderID, readoffset, writeoffset, size);
	}

}
