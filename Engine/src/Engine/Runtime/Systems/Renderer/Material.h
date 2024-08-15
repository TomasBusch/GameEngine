#pragma once

#include "ShaderGraph.h"
#include "Texture.h"

namespace Engine {
	class Material {
		ShaderGraph m_Shader;
		std::vector<ITexture> m_Maps;
	};
}