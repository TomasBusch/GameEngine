#include "pch.hpp"

#include "VertexBuffer.hpp"

#include "Engine/Core/PlatformDetection.hpp"

#ifdef OPENGL_API
#include "Platform/RenderAPIs/OpenGL/OpenGLVertexBuffer.hpp"
#endif
#ifdef VULKAN_API
#include "Platform/RenderAPIs/Vulkan/VulkanVertexBuffer.hpp"
#endif
#ifdef D3D11_API
#include "Platform/RenderAPIs/D3D11/D3D11VertexBuffer.hpp"
#endif
#ifdef D3D12_API
#include "Platform/RenderAPIs/D3D12/D3D12VertexBuffer.hpp"
#endif
#ifdef METAL_API
#include "Platform/RenderAPIs/Metal/MetalVertexBuffer.hpp"
#endif

namespace Engine {

	Ref<VertexBuffer> VertexBuffer::Create(RenderAPI* api)
	{
		switch (api->getRenderAPI())
		{
		case RenderAPI::API::NONE:   ENGINE_BREAK("No rendering api was detected, remember to initialize a rendering api"); return nullptr;
		case RenderAPI::API::OGL4:   return CreateRef<OpenGLVertexBuffer>();
		case RenderAPI::API::VULKAN: ENGINE_BREAK("RenderAPI::API::VULKAN is not currently supported."); return nullptr;
		case RenderAPI::API::D3D11:  ENGINE_BREAK("RenderAPI::API::D3D11 is not currently supported."); return nullptr;
		case RenderAPI::API::D3D12:  ENGINE_BREAK("RenderAPI::API::D3D12 is not currently supported."); return nullptr;
		case RenderAPI::API::METAL:  ENGINE_BREAK("RenderAPI::API::METAL is not currently supported."); return nullptr;
		}

		ENGINE_BREAK("Unknown RendererAPI!");
		return nullptr;
	}

}