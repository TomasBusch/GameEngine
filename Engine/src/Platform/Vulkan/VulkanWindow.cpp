#include "VulkanWindow.h"

#include "config.h"

#include <GLFW/glfw3.h>
#include <glad/vulkan.h>

Engine::VulkanWindow::VulkanWindow(WindowParams& params)
	:m_Width(params.width), m_Height(params.height), m_WindowHandle(nullptr), VK_Instance(nullptr)
{

}

Engine::VulkanWindow::~VulkanWindow()
{

}

void Engine::VulkanWindow::Init()
{
	//--Hints--
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);


	if (!glfwVulkanSupported())
	{
		return;
	}

	if (!glfwInit())
		return;

	m_WindowHandle = glfwCreateWindow(640, 480, "Vulkan Window", NULL, NULL);
	if (!m_WindowHandle)
	{
		glfwTerminate();
		return;
	}
}





void Engine::VulkanWindow::OnUpdate()
{
	glfwSwapBuffers(m_WindowHandle);
	glfwPollEvents();
}

void Engine::VulkanWindow::Shutdown()
{
	vkDestroyInstance(VK_Instance, nullptr);
	glfwTerminate();
}

bool Engine::VulkanWindow::ShouldClose()
{
	return glfwWindowShouldClose(m_WindowHandle);
}

GLFWwindow* Engine::VulkanWindow::GetNativeHandle()
{
	return m_WindowHandle;
}

void Engine::VulkanWindow::createInstance()
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan Game Engine";
	appInfo.applicationVersion = VK_MAKE_API_VERSION(
		VulkanEngine::cmake::project_version_major ,
		VulkanEngine::cmake::project_version_minor ,
		VulkanEngine::cmake::project_version_patch ,
		VulkanEngine::cmake::project_version_tweak
	);
	appInfo.pEngineName = "VulkanEngine";
	appInfo.engineVersion = VK_MAKE_API_VERSION(
		VulkanEngine::cmake::project_version_major,
		VulkanEngine::cmake::project_version_minor,
		VulkanEngine::cmake::project_version_patch,
		VulkanEngine::cmake::project_version_tweak
	);
	appInfo.apiVersion = VK_MAKE_API_VERSION(
		VulkanEngine::cmake::project_version_major,
		VulkanEngine::cmake::project_version_minor,
		VulkanEngine::cmake::project_version_patch,
		VulkanEngine::cmake::project_version_tweak
	);

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	std::uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;

	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &VK_Instance) != VK_SUCCESS) {
		//return error
		return;
	}

}

void Engine::VulkanWindow::enableValidationLayers()
{
	VK_ValidationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};
}

