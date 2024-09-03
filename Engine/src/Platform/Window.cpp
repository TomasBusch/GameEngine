#include "Engine/Core/Base.hpp"

#include "Platform/Window.hpp"
#include "Platform/OpenGL/OpenGLWindow.hpp"
#include "Engine/RenderAPI/RenderAPI.hpp"


namespace Engine {
	Scope<Window> Engine::Window::Create(Window::Params& params) {
		switch (params.RenderAPI)
		{
		case Engine::RenderAPI::OPENGL : 
		{
			return CreateScope<OpenGLWindow>(params);
		}
			break;
		case Engine::RenderAPI::VULKAN :
		{
			ENGINE_CORE_ASSERT(false, "Vulkan not currently supported");
		}
		break;
		case Engine::RenderAPI::D3D11 :
		{
			ENGINE_CORE_ASSERT(false, "D3D11 not currently supported");
		}
		break;
		case Engine::RenderAPI::D3D12 :
		{
			ENGINE_CORE_ASSERT(false, "D3D12 not currently supported");
		}
		break;
		}

	}
}