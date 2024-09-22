#pragma once

#include "Engine/RenderAPI/Buffer.hpp"

#include <glad/gl.h>

namespace Engine::RenderAPI {
	
	enum class BufferTarget {
		VERTEX = GL_ARRAY_BUFFER,
		INDEX = GL_ELEMENT_ARRAY_BUFFER,
		UNIFORM = GL_UNIFORM_BUFFER,
		COPY_READ = GL_COPY_READ_BUFFER,
		COPY_WRITE = GL_COPY_WRITE_BUFFER,
		ATOMIC_COUNTER = GL_ATOMIC_COUNTER_BUFFER,
		DISPATCH_INDIRECT = GL_DISPATCH_INDIRECT_BUFFER,
		DRAW_INDIRECT = GL_DRAW_INDIRECT_BUFFER,
		PIXEL_PACK = GL_PIXEL_PACK_BUFFER,
		PIXEL_UNPACK = GL_PIXEL_UNPACK_BUFFER,
		QUERY = GL_QUERY_BUFFER,
		SHADER_STORAGE = GL_SHADER_STORAGE_BUFFER,
		TEXTURE = GL_TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
	};

	enum class ImmutableUsage {
		STATIC_STORAGE_BIT = 0,
		MAP_READ_BIT = GL_MAP_READ_BIT,
		MAP_WRITE_BIT = GL_MAP_WRITE_BIT,
		MAP_PERSISTENT_READ_BIT = GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT,
		MAP_PERSISTENT_WRITE_BIT = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT,
		MAP_PERSISTENT_COHERENT_BIT = GL_MAP_COHERENT_BIT | GL_MAP_PERSISTENT_BIT,
		DYNAMIC_STORAGE_BIT = GL_DYNAMIC_STORAGE_BIT,
		CLIENT_STORAGE_BIT = GL_CLIENT_STORAGE_BIT,
	};

	enum class MutableUsage {
		STREAM_DRAW = GL_STREAM_DRAW,
		STREAM_READ = GL_STREAM_READ,
		STREAM_COPY = GL_STREAM_COPY,
		STATIC_DRAW = GL_STATIC_DRAW,
		STATIC_READ = GL_STATIC_READ,
		STATIC_COPY = GL_STATIC_COPY,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		DYNAMIC_COPY = GL_DYNAMIC_COPY,
	};

	enum class MapAccessPolicy {
		READ_ONLY = GL_READ_ONLY,
		WRITE_ONLY = GL_WRITE_ONLY,
		READ_WRITE = GL_READ_WRITE,
	};

	enum class InternalFormat {        /*|Base Type|Nº Components|Normalized|   Component   |*/
		                               /*|---------|-------------|----------| 0 | 1 | 2 | 3 |*/
		R8 = GL_R8,                    /*|  ubyte  |      1      |    Y     | R | 0 | 0 | 1 |*/
		R16 = GL_R16,                  /*|  ushort |      1      |    Y     | R | 0 | 0 | 1 |*/
		R16F = GL_R16F,                /*|  halff  |      1      |    N     | R | 0 | 0 | 1 |*/
		R32F = GL_R32F,                /*|  float  |      1      |    N     | R | 0 | 0 | 1 |*/
		R8I = GL_R8I,                  /*|  byte   |      1      |    N     | R | 0 | 0 | 1 |*/
		R16I = GL_R16I,                /*|  short  |      1      |    N     | R | 0 | 0 | 1 |*/
		R32I = GL_R32I,                /*|  int    |      1      |    N     | R | 0 | 0 | 1 |*/
		R8UI = GL_R8UI,                /*|  ubyte  |      1      |    N     | R | 0 | 0 | 1 |*/
		R16UI = GL_R16UI,              /*|  ushort |      1      |    N     | R | 0 | 0 | 1 |*/
		R32UI = GL_R32UI,              /*|  uint   |      1      |    N     | R | 0 | 0 | 1 |*/
		RG8 = GL_RG8,                  /*|  ubyte  |      2      |    Y     | R | G | 0 | 1 |*/
		RG16 = GL_RG16,                /*|  ushort |      2      |    Y     | R | G | 0 | 1 |*/
		RG16F = GL_RG16F,              /*|  halff  |      2      |    N     | R | G | 0 | 1 |*/
		RG32F = GL_RG32F,              /*|  float  |      2      |    N     | R | G | 0 | 1 |*/
		RG8I = GL_RG8I,                /*|  byte   |      2      |    N     | R | G | 0 | 1 |*/
		RG16I = GL_RG16I,              /*|  short  |      2      |    N     | R | G | 0 | 1 |*/
		RG32I = GL_RG32I,              /*|  int    |      2      |    N     | R | G | 0 | 1 |*/
		RG8UI = GL_RG8UI,              /*|  ubyte  |      2      |    N     | R | G | 0 | 1 |*/
		RG16UI = GL_RG16UI,            /*|  ushort |      2      |    N     | R | G | 0 | 1 |*/
		RG32UI = GL_RG32UI,            /*|  uint   |      2      |    N     | R | G | 0 | 1 |*/
		RGB32F = GL_RGB32F,            /*|  float  |      3      |    N     | R | G | B | 1 |*/
		RGB32I = GL_RGB32I,            /*|  int    |      3      |    N     | R | G | B | 1 |*/
		RGB32UI = GL_RGB32UI,          /*|  uint   |      3      |    N     | R | G | B | 1 |*/
		RGBA8 = GL_RGBA8,              /*|  uint   |      4      |    Y     | R | G | B | A |*/
		RGBA16 = GL_RGBA16,            /*|  short  |      4      |    Y     | R | G | B | A |*/
		RGBA16F = GL_RGBA16F,          /*|  halff  |      4      |    N     | R | G | B | A |*/
		RGBA32F = GL_RGBA32F,          /*|  float  |      4      |    N     | R | G | B | A |*/
		RGBA8I = GL_RGBA8I,            /*|  byte   |      4      |    N     | R | G | B | A |*/
		RGBA16I = GL_RGBA16I,          /*|  short  |      4      |    N     | R | G | B | A |*/
		RGBA32I = GL_RGBA32I,          /*|  int    |      4      |    N     | R | G | B | A |*/
		RGBA8UI = GL_RGBA8UI,          /*|  ubyte  |      4      |    N     | R | G | B | A |*/
		RGBA16UI = GL_RGBA16UI,        /*|  ushort |      4      |    N     | R | G | B | A |*/
		RGBA32UI = GL_RGBA32UI,        /*|  uint   |      4      |    N     | R | G | B | A |*/
	};                                 /*----------------------------------------------------*/

	class OpenGLBuffer : public Buffer {
	public:
	protected:
		OpenGLBuffer(std::size_t size)
			:m_Size(size), m_RenderID(0)
		{}

		virtual ~OpenGLBuffer() = default;

	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetData(std::uintptr_t offset, std::size_t size, const void *data) = 0;
		virtual void GetData(std::uintptr_t offset, std::size_t size, void *data) = 0;
		//virtual void Clear(InternalFormat internal_format, std::uintptr_t offset, std::size_t size, ) = 0;
		virtual void Invalidate() = 0;
		virtual void Invalidate(std::uintptr_t offset, std::size_t size) = 0;
		virtual void Map(void** data, MapAccessPolicy access) = 0;
		virtual void Map(void** data, MapAccessPolicy access, std::uintptr_t offset, std::size_t size) = 0;
		virtual void Unmap() = 0;

		static void Copy(OpenGLBuffer& readbuffer, OpenGLBuffer& writebuffer);
		static void Copy(OpenGLBuffer& readbuffer, OpenGLBuffer& writebuffer, std::uintptr_t readoffset, std::uintptr_t writeoffset, std::size_t size);
	private:
		uint32_t m_RenderID;
		std::size_t m_Size;
	};


	template<
		BufferTarget _target, 
		MutableUsage _usage
	>
	class OpenGLMutableBuffer : public OpenGLBuffer {
	public:
		OpenGLMutableBuffer(
			std::size_t size,
			const void* data
		)
			:OpenGLBuffer(size)
		{
			glCreateBuffers(1, &m_RenderID);
			glNamedBufferData(m_RenderID, size, data, _usage);
		};

		virtual ~OpenGLMutableBuffer()
		{
			glDeleteBuffers(1, &m_RenderID);
		};

		virtual void Bind() override
		{
			glBindBuffer(_target, m_RenderID);
		};

		virtual void Unbind() override
		{
			glBindBuffer(_target, 0);
		};

		virtual void SetData(std::uintptr_t offset, std::size_t size, const void* data) override
		{
			glNamedBufferSubData(m_RenderID, offset, size, data);
		};

		virtual void GetData(std::uintptr_t offset, std::size_t size, void* data) override
		{
			glGetNamedBufferSubData(m_RenderID, offset, size, data);
		};

		virtual void Invalidate() override
		{
			glInvalidateBufferData(m_RenderID);
		};

		virtual void Invalidate(std::uintptr_t offset, std::size_t size) override
		{
			glInvalidateBufferSubData(m_RenderID, offset, size);
		};

		virtual void Map(void** data, MapAccessPolicy access) override
		{
			*data = glMapNamedBuffer(m_RenderID, access);
		};

		virtual void Map(void** data, MapAccessPolicy access, std::uintptr_t offset, std::size_t size) override
		{
			*data = glMapNamedBufferRange(m_RenderID, offset, size, access);
		};

		virtual void Unmap() override
		{
			glUnmapNamedBuffer(m_RenderID);
		};
	};


	template<
		BufferTarget _target,
		ImmutableUsage _usage
	>
	class OpenGLImutableBuffer : public OpenGLBuffer {
	public:
		OpenGLImutableBuffer(
			std::size_t size,
			const void* data
		)
			:OpenGLBuffer(size)
		{
			glCreateBuffers(1, &m_RenderID);
			glNamedBufferStorage(m_RenderID, size, data, _usage);
		};

		virtual void Bind() override
		{
			glBindBuffer(_target, m_RenderID);
		};

		virtual void Unbind() override
		{
			glBindBuffer(_target, 0);
		};

		virtual void SetData(std::uintptr_t offset, std::size_t size, const void* data) override
		{
			ENGINE_CORE_ASSERT((_usage & ImmutableUsage::DYNAMIC_STORAGE_BIT) == ImmutableUsage::DYNAMIC_STORAGE_BIT,
				"Setting data on immutable buffers is only allow for buffers created with DYNAMIC_STORAGE_BIT"
			)
			glNamedBufferSubData(m_RenderID, offset, size, data);
		};

		virtual void GetData(std::uintptr_t offset, std::size_t size, void* data) override
		{
			glGetNamedBufferSubData(m_RenderID, offset, size, data);
		};

		virtual void Invalidate() override
		{
			glInvalidateBufferData(m_RenderID);
		};

		virtual void Invalidate(std::uintptr_t offset, std::size_t size) override
		{
			glInvalidateBufferSubData(m_RenderID, offset, size);
		};

		virtual void Map(void** data, MapAccessPolicy access) override
		{
			*data = glMapNamedBuffer(m_RenderID, access);
		};

		virtual void Map(void** data, MapAccessPolicy access, std::uintptr_t offset, std::size_t size) override
		{
			*data = glMapNamedBufferRange(m_RenderID, offset, size, access);
		};

		virtual void Unmap() override
		{
			glUnmapNamedBuffer(m_RenderID);
		};

	};

	//Vertex Buffers
	using OpenGLStaticVertexBuffer = OpenGLMutableBuffer<BufferTarget::VERTEX, MutableUsage::STATIC_DRAW>;
	using OpenGLDynamicVertexBuffer = OpenGLMutableBuffer<BufferTarget::VERTEX, MutableUsage::DYNAMIC_DRAW>;
	using OpenGLStreamVertexBuffer = OpenGLMutableBuffer<BufferTarget::VERTEX, MutableUsage::STREAM_DRAW>;

	//Index Buffers
	using OpenGLStaticIndexBuffer = OpenGLMutableBuffer<BufferTarget::INDEX, MutableUsage::STATIC_DRAW>;
	using OpenGLDynamicIndexBuffer = OpenGLMutableBuffer<BufferTarget::INDEX, MutableUsage::DYNAMIC_DRAW>;
	using OpenGLStreamIndexBuffer = OpenGLMutableBuffer<BufferTarget::INDEX, MutableUsage::STREAM_DRAW>;
}