#pragma once

namespace Engine {
	enum RenderAPI {
		NONE = 0,
		OPENGL, //Only one currently supported
		VULKAN,
		METAL,
		D3D11,
		D3D12,
	};
}