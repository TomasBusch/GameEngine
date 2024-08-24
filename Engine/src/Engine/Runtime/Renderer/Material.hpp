#pragma once

#include "ShaderGraph.hpp"
#include "Texture.hpp"

namespace Engine {
	class Material {
		ShaderGraph m_Shader;
		std::vector<ITexture> m_Maps;
	};
}