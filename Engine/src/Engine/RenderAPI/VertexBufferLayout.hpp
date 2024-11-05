#pragma once

#include "pch.hpp"

namespace Engine {
	

	struct VertexAttributeDescriptor {
		enum class Format {
			BYTE,
			INT8 = BYTE,
			UBYTE,
			UINT8 = UBYTE,
			INT16,
			UINT16,
			INT32,
			UINT32,
			FLOAT16,
			FLOAT32,
			VEC1 = FLOAT32,
			FLOAT64,
			DOUBLE = FLOAT64,
			FIXED,
			INT_2_10_10_10_REV,
			UINT_2_10_10_10_REV,
			UINT_10F_11F_11F_REV,
		};

		Format format;
		uint32_t location;
		intptr_t offset;
		uint8_t count;
		bool normalized;

		uint16_t getSize() {
			switch (format) {
				case Format::INT8:
				case Format::UINT8:               { return 8; }  break;
				case Format::INT16:
				case Format::UINT16:
				case Format::FLOAT16:             { return 16; } break;
				case Format::INT32:
				case Format::UINT32:
				case Format::FLOAT32:             { return 32; } break;              
				case Format::FLOAT64:             { return 64; } break;             
				case Format::FIXED:               { return 32; } break;
				case Format::INT_2_10_10_10_REV:
				case Format::UINT_2_10_10_10_REV:
				case Format::UINT_10F_11F_11F_REV:{ return 32; } break;
			}
		}
	};

	class VertexBufferLayout {
	private:
		std::vector<VertexAttributeDescriptor> m_DescriptorList{};
		uint32_t m_Stride = 0;
	public: 
		VertexBufferLayout() = default;
		VertexBufferLayout(std::vector<VertexAttributeDescriptor> descriptors, uint32_t stride) 
			:m_DescriptorList(descriptors), m_Stride(stride) {}
		~VertexBufferLayout() = default;

		std::vector<VertexAttributeDescriptor>& getDescriptors() { m_DescriptorList; };
		uint32_t getStride() { m_Stride; }
	};
}