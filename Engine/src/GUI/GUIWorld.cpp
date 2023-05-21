#include "GUI/GUIWorld.h"

namespace Bambo
{
	void GUIWorld::Initialize()
	{
		IMGUI_CHECKVERSION();
		m_context = ImGui::CreateContext();
		
		ImGui::StyleColorsDark();

		GLFWwindow* window = static_cast<GLFWwindow*>(WindowManager::Get()->GetWindow().GetWindowPtr());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void GUIWorld::Dispose()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext(m_context);
	}

	void GUIWorld::StartFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGuizmo::BeginFrame();
	}

	void GUIWorld::EndFrame()
	{
		ImGuiIO& io = ImGui::GetIO();
		Window& window = WindowManager::Get()->GetWindow();
		io.DisplaySize = ImVec2((float)window.GetWidth(), (float)window.GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}