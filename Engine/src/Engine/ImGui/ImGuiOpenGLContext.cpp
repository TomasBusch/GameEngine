#include "ImGuiOpenGLContext.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

Engine::ImGuiOpenGLContext::ImGuiOpenGLContext(Window* window)
    :ImGuiContext(window)
{

}

Engine::ImGuiOpenGLContext::~ImGuiOpenGLContext()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Engine::ImGuiOpenGLContext::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_ContextData.io = &ImGui::GetIO();
    m_ContextData.io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    m_ContextData.io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    m_ContextData.io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    m_ContextData.io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //m_ContextData.io->ConfigViewportsNoAutoMerge = true;
    //m_ContextData.io->ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    m_ContextData.style = &ImGui::GetStyle();
    if (m_ContextData.io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        m_ContextData.style->WindowRounding = 0.0f;
        m_ContextData.style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_Window->getNativeHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Engine::ImGuiOpenGLContext::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Engine::ImGuiOpenGLContext::EndFrame()
{
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (m_ContextData.io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}