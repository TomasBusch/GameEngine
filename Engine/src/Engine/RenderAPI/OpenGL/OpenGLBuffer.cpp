#include "Engine/Core/Base.hpp"

#include "OpenGLBuffer.hpp"

#include <glad/gl.h>

namespace Engine::RenderAPI {

	OpenGLBuffer::OpenGLBuffer(BufferTarget target, bool is_mutable, std::size_t size, const void *data)
		:m_Mutable(is_mutable), m_Target(target), m_Size(size)
	{
		glCreateBuffers(1, &m_RenderID);
		if (is_mutable) {
			glNamedBufferStorage(m_RenderID, size, data, ImmutableUsage::STATIC_STORAGE_BIT);
		}
		else {
			glNamedBufferData(m_RenderID, size, data, MutableUsage::DYNAMIC_DRAW);
		}
	}

	OpenGLBuffer::~OpenGLBuffer() {
		glDeleteBuffers(1, &m_RenderID);
	}

	void OpenGLBuffer::Bind()
	{
		glBindBuffer(m_Target, m_RenderID);
	}

	void OpenGLBuffer::UnBind()
	{
		glBindBuffer(m_Target, 0);
	}

	void OpenGLBuffer::SetData(std::uintptr_t offset, std::size_t size, const void* data)
	{
		if (m_Mutable) {
			glNamedBufferSubData(m_RenderID, offset, size, data);
		}
	}

	void OpenGLBuffer::GetData(std::uintptr_t offset, std::size_t size, void* data)
	{
		glGetNamedBufferSubData(m_RenderID, offset, size, data);
	}

	//void OpenGLBuffer::Clear(std::uintptr_t offset, std::size_t size, )
	//{

	//}

	void OpenGLBuffer::Invalidate()
	{
		glInvalidateBufferData(m_RenderID);
	}

	void OpenGLBuffer::Invalidate(std::uintptr_t offset, std::size_t size)
	{
		glInvalidateBufferSubData(m_RenderID, offset, size);
	}

	void OpenGLBuffer::Map(void **data, MapAccessPolicy access)
	{
		*data = glMapNamedBuffer(m_RenderID, access);
	}

	void OpenGLBuffer::Map(void** data, MapAccessPolicy access, std::uintptr_t offset, std::size_t size)
	{
		*data = glMapNamedBufferRange(m_RenderID, offset, size, access);
	}

	void OpenGLBuffer::UnMap()
	{
		glUnmapNamedBuffer(m_RenderID);
	}

	void OpenGLBuffer::Copy(OpenGLBuffer& readbuffer, OpenGLBuffer& writebuffer)
	{
		ENGINE_ASSERT(readbuffer.m_Size <= writebuffer.m_Size, "ERROR: Cannot copy contents of one buffer into a smaller buffer");

		glCopyNamedBufferSubData(readbuffer.m_RenderID, writebuffer.m_RenderID, 0, 0, readbuffer.m_Size);
	}

	void OpenGLBuffer::Copy(OpenGLBuffer& readbuffer, OpenGLBuffer& writebuffer, std::uintptr_t readoffset, std::uintptr_t writeoffset, std::size_t size)
	{
		ENGINE_ASSERT(readbuffer.m_Size <= (readoffset + size), "ERROR: Cannot copy from outside the buffer's memory");
		ENGINE_ASSERT(writebuffer.m_Size <= (writeoffset + size), "ERROR: Write buffer does not have enough memory to copy into");

		glCopyNamedBufferSubData(readbuffer.m_RenderID, writebuffer.m_RenderID, readoffset, writeoffset, size);
	}

}
