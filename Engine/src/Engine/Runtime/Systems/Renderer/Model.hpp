#pragma once
#include "pch.h"

#include "glm/glm.hpp"

#include "Mesh.h"

namespace Engine {
	class Model {
	public:

	private:
		std::vector<Mesh> m_Meshes;
		glm::mat4 m_ModelMatrix;
	};
}