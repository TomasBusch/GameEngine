#pragma once

#include "ImguiContext.h"
#include "Platform/OpenGL/OpenGLWindow.h"

namespace Engine {
	class ImguiOpenGLContext : public ImguiContext {
	public:
		ImguiOpenGLContext() = default;
		~ImguiOpenGLContext();

		void Init(OpenGLWindow* window, const std::string& glsl_version);
		virtual void Render() override;
	};
}