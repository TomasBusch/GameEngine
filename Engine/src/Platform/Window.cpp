#include "Engine/Core/Base.h"

#include "Platform/Window.h"
#include "Platform/OpenGL/OpenGLWindow.h"
#include "Engine/RenderAPI/RenderAPI.h"


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
			ENGINE_ASSERT(false, "Vulkan not currently supported");
		}
		break;
		case Engine::RenderAPI::D3D11 :
		{
			ENGINE_ASSERT(false, "D3D11 not currently supported");
		}
		break;
		case Engine::RenderAPI::D3D12 :
		{
			ENGINE_ASSERT(false, "D3D12 not currently supported");
		}
		break;
		}

	}
}