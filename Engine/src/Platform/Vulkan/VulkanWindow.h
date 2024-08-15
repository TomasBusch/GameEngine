#pragma once

#include "Platform/Window.h"

#include <GLFW/glfw3.h>
#include <glad/vulkan.h>

namespace Engine {
	class VulkanWindow : public Window {
	public:
		VulkanWindow() = delete;
		VulkanWindow(Window::Params& params);
		virtual ~VulkanWindow();

		virtual void Init() override;
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		virtual bool ShouldClose() override;

		GLFWwindow* GetNativeHandle();
	private:
		void createInstance();
		void enableValidationLayers();
	private:
		GLFWwindow* m_WindowHandle;
		VkInstance VK_Instance;
		std::vector<const char*> VK_ValidationLayers;

		std::uint32_t m_Width, m_Height;
	};
}