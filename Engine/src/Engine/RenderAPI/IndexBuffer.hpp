#pragma once

namespace Engine {
	class IndexBuffer {
	public:
		IndexBuffer() = default;
		virtual ~IndexBuffer() = default;
		IndexBuffer(const IndexBuffer&) = delete;

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

		virtual void copyTo(IndexBuffer& writebuffer) = 0;
		virtual void copyTo(IndexBuffer& writebuffer, std::uintptr_t readoffset, std::uintptr_t writeoffset, std::size_t size) = 0;
	};
}