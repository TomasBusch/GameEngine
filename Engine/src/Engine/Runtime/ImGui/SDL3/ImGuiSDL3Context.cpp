#include "ImGuiSDL3Context.hpp"

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL2/SDL.h>

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
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void Engine::ImGuiSDL3Context::Init(void* platform_data)
{
    PlatformData* platform = (PlatformData*)platform_data;

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
    //SDL_Window* window = SDL_GL_GetCurrentWindow();
    //SDL_GLContextState* context = SDL_GL_GetCurrentContext();

    ImGui_ImplSDL3_InitForOpenGL(platform->m_WindowHandle, platform->m_Context);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Engine::ImGuiSDL3Context::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void Engine::ImGuiSDL3Context::EndFrame()
{
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (m_ImGuiData->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
}

//void Engine::ImGuiSDL3Context::Render(Callback<> cb) {
//
//
//    cb();
//
//}
