#pragma once
#include "pch.h"

#include "Engine/RenderAPI/Framebuffer.hpp"
#include "Engine/RenderAPI/Texture.hpp"

#include <glad/gl.h>

namespace Engine {
	class OpenGLFramebuffer : public Framebuffer {
	private:
		uint32_t m_RenderID;

	public:
		OpenGLFramebuffer(Texture& texture)
			:
		{
			glCreateFramebuffers();
		}

		~OpenGLFramebuffer() 
		{
			glDeleteFramebuffers();
		}
	};
}