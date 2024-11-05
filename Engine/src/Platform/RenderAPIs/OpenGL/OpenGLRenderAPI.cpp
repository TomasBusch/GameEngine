#include "OpenGLRenderAPI.hpp"

#define COMMANDS_PER_FRAME 10000

Engine::OpenGLRenderAPI::OpenGLRenderAPI()
{
	m_CommandList.reserve(COMMANDS_PER_FRAME);
}

Engine::OpenGLRenderAPI::~OpenGLRenderAPI()
{

}

void Engine::OpenGLRenderAPI::beginFrame()
{
	m_CommandList.clear();
}

void Engine::OpenGLRenderAPI::endFrame()
{
	draw();
}

void Engine::OpenGLRenderAPI::submit(Command command)
{
	m_CommandList.emplace_back(command);
}

void Engine::OpenGLRenderAPI::draw()
{
	for (Command command : m_CommandList) {
		static_cast<DrawCommand>(command);
	}
}

void Engine::OpenGLRenderAPI::compute()
{

}


