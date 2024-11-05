#pragma once

#include "Command.hpp"

namespace Engine {
	class RenderAPI {
	public:
		enum class API {
			NONE = 0,
			OGL4, //Only one currently supported
			VULKAN,
			METAL,
			D3D11,
			D3D12,
		};

		RenderAPI() = default;
		virtual ~RenderAPI() = default;

		virtual void beginFrame() = 0;
		virtual void endFrame() = 0;
		virtual void submit(Command command) = 0;
		RenderAPI::API getRenderAPI() { return m_RenderAPI; }
	private:
		RenderAPI::API m_RenderAPI = RenderAPI::API::NONE;
	};
}