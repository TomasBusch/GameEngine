#include "Renderer.hpp"

namespace Engine {

	Renderer::Renderer(Ref<RenderContext> render_context)
		:m_RenderContext(render_context)
	{
		
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Draw(Scene& scene)
	{

	}

	void Renderer::Draw()
	{
		RenderCommand rObj;
		rObj.vertexBuffer = m_VertexBuffer.get();
		rObj.indexBuffer = m_IndexBuffer.get();
		rObj.shader = m_Shader.get();
		rObj.uniformBuffer = m_MVPUniformBuffer.get();

		m_RenderAPI->BeginFrame();

		m_RenderContext->Draw(rObj);

		m_RenderAPI->EndFrame();
	}

}
