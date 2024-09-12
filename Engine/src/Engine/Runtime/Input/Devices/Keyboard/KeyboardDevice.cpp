#include "KeyboardDevice.hpp"

#include "Platform/OpenGL/GLFWOpenGLWindow.hpp"

#include <GLFW/glfw3.h>

bool Engine::Input::KeyboardDevice::isKeyPressed(const Keycode key)
{
	auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->getNativeHandle());

	return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Engine::Input::KeyboardDevice::isKeyReleased(const Keycode key)
{
	auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow()->getNativeHandle());

	return glfwGetKey(window, key) == GLFW_RELEASE;
}
