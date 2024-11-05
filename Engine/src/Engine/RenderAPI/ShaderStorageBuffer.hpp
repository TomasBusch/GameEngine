#pragma once

#include "Buffer.hpp"

namespace Engine {
	class ShaderStorageBuffer {
	public:
		ShaderStorageBuffer() = default;
		virtual ~ShaderStorageBuffer() = default;
		ShaderStorageBuffer(const ShaderStorageBuffer&) = delete;
	};
}