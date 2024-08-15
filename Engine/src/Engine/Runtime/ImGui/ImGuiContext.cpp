#include "Engine/Core/Base.h"

#include "ImGuiContext.h"
#include "OpenGL/ImGuiOpenGLContext.h"

namespace Engine {

	Scope<ImGuiContext> ImGuiContext::Create(Window* window)
	{
		switch (window->GetRenderAPIType())
		{
		case RenderAPI::OPENGL :
		{
			return CreateScope<ImGuiOpenGLContext>(window);
		}
		break;
		case RenderAPI::VULKAN :
		{
			ENGINE_ASSERT(false, "Vulkan is not currently supported");
		}
		break;

		case RenderAPI::D3D11 :
		{
			ENGINE_ASSERT(false, "D3D11 is not currently supported");
		}
		break;

		case RenderAPI::D3D12 :
		{
			ENGINE_ASSERT(false, "D3D12 is not currently supported");
		}
		break;
		}
	}
}
