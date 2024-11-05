#pragma once

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "UniformBuffer.hpp"

namespace Engine {

	namespace API {
		enum class CommandType {
			NONE,
			DRAW,
			DRAW_INDEX,
			COMPUTE,
		};

		enum class DrawPrimitive {
			DRAW_POINTS,
			DRAW_LINE_STRIP,
			DRAW_LINE_LOOP,
			DRAW_LINES,
			DRAW_LINE_STRIP_ADJACENCY,
			DRAW_LINES_ADJACENCY,
			DRAW_TRIANGLE_STRIP,
			DRAW_TRIANGLE_FAN,
			DRAW_TRIANGLES,
			DRAW_TRIANGLE_STRIP_ADJACENCY,
			DRAW_TRIANGLES_ADJACENCY,
			DRAW_PATCHES
		};
	}

	struct Command {
		API::CommandType type = API::CommandType::NONE;
	};

	struct DrawIndexedCommand : public Command {


		API::CommandType type = API::CommandType::DRAW_INDEX;
		API::DrawPrimitive primitive;

		uint32_t elementCount;
		uint32_t instanceCount;
		uint32_t firstIndex;
		uint32_t baseVertex;
		uint32_t baseInstance;
	};
	
	
	struct ComputeCommand : public Command{
		API::CommandType type = API::CommandType::COMPUTE;

	};
}

