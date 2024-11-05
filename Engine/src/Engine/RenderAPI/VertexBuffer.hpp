#pragma once

#include "RenderAPI.hpp"

namespace Engine {
	class VertexBuffer {
	public:
		VertexBuffer() = default;
		virtual ~VertexBuffer() = default;
		VertexBuffer(const VertexBuffer&) = delete;

		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void setData(std::uintptr_t offset, std::size_t size, const void* data) = 0;
		virtual void getData(std::uintptr_t offset, std::size_t size, void* data) = 0;
		//virtual void Clear(InternalFormat internal_format, std::uintptr_t offset, std::size_t size, ) = 0;
		virtual void invalidate() = 0;
		virtual void invalidate(std::uintptr_t offset, std::size_t size) = 0;
		virtual void map(void** data/*, MapAccessPolicy access*/) = 0;
		virtual void map(void** data/*, MapAccessPolicy access*/, std::uintptr_t offset, std::size_t size) = 0;
		virtual void unmap() = 0;

		virtual void copyTo(VertexBuffer& writebuffer) = 0;
		virtual void copyTo(VertexBuffer& writebuffer, std::uintptr_t readoffset, std::uintptr_t writeoffset, std::size_t size) = 0;

		static Ref<VertexBuffer> Create(RenderAPI* api);
	};


}