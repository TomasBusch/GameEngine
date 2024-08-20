#pragma once

namespace Engine::RenderAPI {

	class Buffer {
	public:
		enum class BufferUsage {
			VERTEX,
			INDEX,
			UNIFORM,
			COPY_READ,
			COPY_WRITE
		};
	public:
		Buffer() = default;
		virtual ~Buffer() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void SetData() = 0;
	};
}