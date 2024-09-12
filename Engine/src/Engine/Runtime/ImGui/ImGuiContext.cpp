#include "Engine/Core/Base.hpp"

#include "ImGuiContext.hpp"
#include "GLFW/ImGuiGLFWContext.hpp"
#include "SDL3/ImGuiSDL3Context.hpp"

namespace Engine {

	template<>
	ImGuiContext* ImGuiContext::Create<ImGuiGLFWContext>()
	{
		if (s_Instance == nullptr) {
			return new ImGuiGLFWContext();
		}
		else {
			ENGINE_CORE_ASSERT(s_Instance->m_ContextType == ImGuiGLFWContext::GetClassContextType(), 
				"Trying to create incompatible ImguiContext and Window types");
			return (ImGuiGLFWContext*)s_Instance;
		}
	}

	template<>
	ImGuiContext* ImGuiContext::Create<ImGuiSDL3Context>()
	{
		if (s_Instance == nullptr) {
			return new ImGuiSDL3Context();
		}
		else {
			ENGINE_CORE_ASSERT(s_Instance->m_ContextType == ImGuiSDL3Context::GetClassContextType(),
				"Trying to create incompatible ImguiContext and Window types");
			return (ImGuiSDL3Context*)s_Instance;
		}
	}
}
