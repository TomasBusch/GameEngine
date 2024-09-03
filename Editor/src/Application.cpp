#include <config.hpp>
#include <Engine.hpp>

#include <filesystem>

#include "GUI/Themes.hpp"

class Editor : public Engine::Application
{
public:
	Editor(const Engine::Application::Specs& specs)
		: Engine::Application(specs)
	{
	#ifdef COMPILER_MSVC
		std::filesystem::path cwd = std::filesystem::current_path();
		std::cout << cwd << std::endl;
	#endif
	}

	~Editor()
	{

	}
protected:
	virtual void OnInit() override 
	{
		setTheme2();
	}

	virtual void ImGuiRender() override
	{
		//Window bools
		static bool show_demo = true;
		static bool widgets_window = true;
		static bool show_demo_window = true;


		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove 
				| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollWithMouse;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("DockSpace");
			//ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(1.0f, 0.0f, 0.f, 1.0f));
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			//ImGui::PopStyleColor();
		}

		if (opt_fullscreen) {
			ImGui::PopStyleVar(3);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File")) {

				if (ImGui::MenuItem("Open Project", "Ctrl+O")) {
					std::cout << "Open File" << std::endl;
				}

				if (ImGui::MenuItem("Save", "Ctrl+S")) {
					std::cout << "Open File" << std::endl;
				}

				if (ImGui::MenuItem("Save As")) {
					std::cout << "Open File" << std::endl;
				}

				if (ImGui::MenuItem("Demo")) {
					show_demo = true;
					show_demo_window = true;
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		if(show_demo_window){
			static float f = 0.0f;
			static int counter = 0;
			static bool checkbox = false;

			ImGui::Begin("Hello, world!", &show_demo_window);                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &checkbox);      // Edit bools storing our window open/close state

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

			if (ImGui::Button("Button")) {                           // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			}
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		if (widgets_window) {
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
			
			ImGui::Begin("Widgets", &widgets_window);
			static bool check = false;
			//ImGui::PushStyleVar();
			ImGui::Checkbox("Check", &check);
			ImGui::Button("Button");
			ImGui::End();

			ImGui::PopStyleVar(1);
		}

		if (show_demo) {
			ImGui::ShowDemoWindow(&show_demo);
		}

		ImGui::End();


		//ImGui::ShowStyleEditor();

	}
};

Engine::Application* Engine::CreateApplication(Engine::Application::Args args)
{
	Application::Specs specs;
	specs.name = "Vulkan Engine";
	specs.workDir = "./";
	specs.cmdLineArgs = args;

	return new Editor(specs);
}