#include "Context.hpp"

#include "Engine/Core/Base.hpp"
#include "OpenGL/OpenGLContext.hpp"

namespace Engine::RenderAPI {
	Scope<Context> Create(RenderAPITypes type) {
		switch (type) {
		case RenderAPITypes::NONE:		return nullptr;
		case RenderAPITypes::OPENGL:	return CreateScope<OpenGLContext>();
		}
	}
}