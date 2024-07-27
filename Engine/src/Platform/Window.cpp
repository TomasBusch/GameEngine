#include "Platform/Window.h"
#include "Platform/OpenGL/OpenGLWindow.h"


namespace Engine {
	Scope<Window> Engine::Window::Create(WindowParams& params) {
		return CreateScope<OpenGLWindow>(params);
	}
}