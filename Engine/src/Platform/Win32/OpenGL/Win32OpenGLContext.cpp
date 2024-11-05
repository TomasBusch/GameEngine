#ifdef WIN_32
#include "Platform/RenderAPIs/OpenGL/OpenGLContext.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

Engine::OpenGLContext::OpenGLContext()
{

}

Engine::OpenGLContext::~OpenGLContext()
{

}

void Engine::OpenGLContext::Init(void* data_ptr)
{
	gladLoadGL(glfwGetProcAddress);
}

void Engine::OpenGLContext::SetVsync(bool vsync)
{
	if (vsync != m_Vsync) {
		glfwSwapInterval(vsync);
		m_Vsync = vsync;
	}
}


#endif //WIN_32