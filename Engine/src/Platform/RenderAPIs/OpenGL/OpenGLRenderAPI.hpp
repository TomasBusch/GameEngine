#pragma once

#include "Engine/RenderAPI/RenderAPI.hpp"

namespace Engine {
	class OpenGLRenderAPI : public RenderAPI {
	public:
		OpenGLRenderAPI();
		virtual ~OpenGLRenderAPI();

		virtual void beginFrame() override;
		virtual void endFrame() override;
		virtual void submit(Command command) override;
	private:
		void draw();
		void compute();
	private:
		std::vector<Command> m_CommandList{};
	};
}