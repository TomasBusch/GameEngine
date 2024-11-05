#pragma once

#include "Engine/Core/Base.hpp"

#include "Engine/Runtime/Scene/Scene.hpp"
#include "Engine/RenderAPI/RenderAPI.hpp"
#include "Engine/RenderAPI/Command.hpp"

namespace Engine {
	class Renderer {
	public:
		Renderer(Ref<RenderAPI> render_context);
		~Renderer();

		void Draw(Scene& scene);
		void Draw();
	private:
		Ref<RenderAPI> m_RenderAPI;
		//TODO: Replace with Model Asset Manager
		Scope<IndexBuffer> m_IndexBuffer;
		Scope<VertexBuffer> m_VertexBuffer;
		
		Scope<Shader> m_Shader;
		
		Scope<UniformBuffer> m_MVPUniformBuffer;
	};
}