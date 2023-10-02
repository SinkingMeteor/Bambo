#include "GUIWorld.h"

namespace BamboEditor
{
	void GUIWorld::Initialize()
	{
		IMGUI_CHECKVERSION();
		m_context = ImGui::CreateContext();
		
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromFileTTF((BamboPaths::EngineResourcesDir / BamboPaths::EngineDefaultFontPath_A).string().c_str(), 18.0f, NULL, io.Fonts->GetGlyphRangesCyrillic());

		GLFWwindow* windowPtr = static_cast<GLFWwindow*>(m_targetWindow->GetWindowPtr());
		
		ImGui_ImplGlfw_InitForOpenGL(windowPtr, true);
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
	}

	void GUIWorld::EndFrame()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)m_targetWindow->GetWidth(), (float)m_targetWindow->GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}