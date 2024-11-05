#pragma once
#include "pch.hpp"
#include "MeshAsset.hpp"

namespace Engine {
	struct ModelAsset {
		std::string filePath;
		std::vector<Scope<MeshAsset>> meshes;
	};
}