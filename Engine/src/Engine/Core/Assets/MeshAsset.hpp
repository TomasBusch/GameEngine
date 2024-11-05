#pragma once
#include "pch.hpp"

#include "MaterialAsset.hpp"

namespace Engine {
	struct MeshAsset {
		void* vertex_data;
		void* index_data;
		Scope<MaterialAsset> material;
	};
}