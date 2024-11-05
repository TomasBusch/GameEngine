#pragma once

#include "Engine/RenderAPI/Shader.hpp"
#include "Engine/RenderAPI/Texture.hpp"

namespace Engine {
	class Material {
		Shader m_Shader;
		std::vector<Texture> m_Maps;
	};
}