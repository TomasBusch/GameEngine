#pragma once
#include "Engine/Core/Base.hpp"

#include <imgui.h>

namespace Engine {

	class ImGuiContext {
	protected:
		ImGuiContext() = default;
		virtual ~ImGuiContext() = default;

		enum class ContextType {
			NONE,
			GLFW,
			SDL3
		};

	public:
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;
		//virtual void Render(Callback<> cb) = 0;
		virtual void Init(void* platform_data) = 0;

		template<typename T>
		static ImGuiContext* Create();

		constexpr static ContextType GetClassContextType() {
			return ContextType::NONE;
		};
	protected:
		ContextType m_ContextType = ContextType::NONE;

	private:
		//TODO consider adding mutext to avoid race condition in singleton creation
		inline static ImGuiContext* s_Instance = nullptr;
	};
}