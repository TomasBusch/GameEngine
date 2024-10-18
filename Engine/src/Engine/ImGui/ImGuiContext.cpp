#include "Engine/Core/Base.hpp"

#include "ImGuiContext.hpp"
#include "ImGuiOpenGLContext.hpp"
//#include "SDL3/ImGuiSDL3Context.hpp"

namespace Engine {

	Scope<ImGuiContext> ImGuiContext::Create(Window* window)
	{
		return CreateScope<ImGuiOpenGLContext>(window);
	}
}
