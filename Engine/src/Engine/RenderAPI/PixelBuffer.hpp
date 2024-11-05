#pragma once

#include "Buffer.hpp"

namespace Engine {
	class PixelBuffer {
	public:
		PixelBuffer() = default;
		virtual ~PixelBuffer() = default;
		PixelBuffer(const PixelBuffer&) = delete;
	};
}