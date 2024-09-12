#include "ImGuiSDL3Context.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

struct Engine::ImGuiSDL3Context::ImguiData {
    ImGuiIO* io;
    ImGuiStyle* style;
};

Engine::ImGuiSDL3Context::ImGuiSDL3Context()
{
    m_ImGuiData = CreateScope<ImguiData>();
    m_ContextType = ContextType::GLFW;
}

Engine::ImGuiSDL3Context::~ImGuiSDL3Context()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Engine::ImGuiSDL3Context::Init(const std::string& API_Version, void* platform_data)
{
    SDL3PlatformData* platform = (SDL3PlatformData*)platform_data;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_ImGuiData->io = &ImGui::GetIO();
    m_ImGuiData->io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    m_ImGuiData->io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    m_ImGuiData->io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    m_ImGuiData->io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //m_ImGuiData->io->ConfigViewportsNoAutoMerge = true;
    //m_ImGuiData->io->ConfigViewportsNoTaskBarIcon = true;


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    m_ImGuiData->style = &ImGui::GetStyle();
    if (m_ImGuiData->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        m_ImGuiData->style->WindowRounding = 0.0f;
        m_ImGuiData->style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    //ImGui_ImplGlfw_InitForOpenGL(platform->m_WindowHandle, true);
    ImGui_ImplOpenGL3_Init(API_Version.c_str());
}

void Engine::ImGuiSDL3Context::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Engine::ImGuiSDL3Context::EndFrame()
{
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (m_ImGuiData->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

//void Engine::ImGuiSDL3Context::Render(Callback<> cb) {
//
//
//    cb();
//
//}
