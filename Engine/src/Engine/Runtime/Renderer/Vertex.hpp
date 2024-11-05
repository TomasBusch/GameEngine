#pragma once

#include "Engine/RenderAPI/VertexBufferLayout.hpp"

namespace Engine {

	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 uv;

		VertexBufferLayout getVertexLayout()
		{
			return VertexBufferLayout(
				{
					{ VertexAttributeDescriptor::Format::FLOAT32, 0, offsetof(Vertex, position), 3, false},
					{ VertexAttributeDescriptor::Format::FLOAT32, 1, offsetof(Vertex, color)   , 4, false},
					{ VertexAttributeDescriptor::Format::FLOAT32, 2, offsetof(Vertex, normal)  , 3, true },
					{ VertexAttributeDescriptor::Format::FLOAT32, 3, offsetof(Vertex, uv)      , 2, false}
				},
				sizeof(Vertex)
			);
		}
	};
}