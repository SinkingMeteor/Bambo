#include "Windows/GameViewport.h"

namespace BamboEditor
{
	GameViewportWindow::GameViewportWindow(SPtr<Bambo::Framebuffer> framebuffer) :
		m_framebuffer(framebuffer),
		m_windowName("Game viewport")
	{}

	void GameViewportWindow::OnGUI()
	{
		if (ImGui::Begin("Game Viewport", nullptr,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse))
		{
			ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

			uint64_t textureID = m_framebuffer->GetTextureID();
			ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

			ImGui::End();
		}
	}
}