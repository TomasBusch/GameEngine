#pragma once

#include "pch.h"

#include "UniformBuffer.hpp"

namespace Engine {
	class Program {
	public:
		Program();
		virtual ~Program() = default;

		virtual uint32_t getUniformBlockIndex(const std::string& block_name) = 0;
		virtual void setUniformBlockBinding(uint32_t block_index, const UniformBuffer& uniform_buffer) = 0;
	};

}