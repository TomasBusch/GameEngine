#pragma once

namespace Engine::RenderAPI {
	enum RenderAPITypes {
		NONE = 0,
		OPENGL, //Only one currently supported
		VULKAN,
		D3D11,
		D3D12,
	};
}