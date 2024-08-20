#include "ImguiOpenGLContext.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

struct Engine::ImGuiOpenGLContext::ImguiData {
    ImGuiIO* io;
    ImGuiStyle* style;
};

Engine::ImGuiOpenGLContext::ImGuiOpenGLContext(Window* window)
    :m_ImGuiData(CreateScope<ImguiData>()), m_Window(window)
{
}

Engine::ImGuiOpenGLContext::~ImGuiOpenGLContext()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Engine::ImGuiOpenGLContext::Init(const std::string& glsl_version)
{
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
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(m_Window->getNativeHandle()), true);
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void Engine::ImGuiOpenGLContext::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

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
