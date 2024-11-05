#pragma once
#include "pch.hpp"

#include "ImageAsset.hpp"
#include "ShaderAsset.hpp"

namespace Engine {
	struct MaterialAsset {
		std::vector<Scope<ImageAsset>> maps;
		Scope<ShaderAsset> shader;
	};
}