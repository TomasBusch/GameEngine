#pragma once

namespace Engine {
	struct ShaderAsset {
		std::string FilePath;

		void* vertexShaderData;
		void* fragmentShaderData;
	};
}