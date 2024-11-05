#pragma once

#include "Vertex.hpp"
#include "Material.hpp"

namespace Engine {
	class Mesh {
	private:
		Vertex* m_Vertices;
		uint32_t* m_Indices;
		Material* m_Material;
	};
}