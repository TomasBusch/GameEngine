#include "Engine/Core/Base.hpp"

#include "Window.hpp"
#include "Engine/RenderAPI/RenderAPI.hpp"
#include "Platform/RenderAPIs/OpenGL/OpenGLWindow.hpp"


namespace Engine {
	Scope<Window> Engine::Window::Create(Window::Params& params) {
		switch (params.renderAPI)
		{
		case Engine::RenderAPI::API::OGL4 :
		{
			return CreateScope<OpenGLWindow>(params);
		}
		break;
		case Engine::RenderAPI::API::VULKAN :
		{
			//return CreateScope<VulkanWindow>(params);
			ENGINE_CORE_BREAK("Vulkan not currently supported");
		}
		break;
		case Engine::RenderAPI::API::D3D11 :
		{
			//return CreateScope<D3D11Window>(params);
			ENGINE_CORE_BREAK("D3D11 not currently supported");
		}
		break;
		case Engine::RenderAPI::API::D3D12 :
		{
			//return CreateScope<D3D12Window>(params);
			ENGINE_CORE_BREAK("D3D12 not currently supported");
		}
		break;
		case Engine::RenderAPI::API::METAL:
		{
			//return CreateScope<MetalWindow>(params);
			ENGINE_CORE_BREAK("METAL not currently supported");
		}
		break;
		}

	}
}