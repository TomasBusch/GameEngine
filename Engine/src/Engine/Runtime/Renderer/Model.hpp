#pragma once
#include "pch.hpp"

#include "glm/glm.hpp"

#include "Mesh.hpp"

namespace Engine {
	class Model {
	private:
		std::vector<Mesh> m_Meshes;
		glm::mat4 m_ModelMatrix;
	};
}