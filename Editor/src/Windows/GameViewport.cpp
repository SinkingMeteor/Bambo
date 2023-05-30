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
			ImVec2 viewportPanelSize = ResizeGameViewport();
			ImVec2 windowSize = ImGui::GetWindowSize();
			float xPos = (windowSize.x - viewportPanelSize.x) * 0.5f;
			float yPos = (windowSize.y - viewportPanelSize.y) * 0.5f;
			ImGui::SetCursorPos(ImVec2{ xPos, yPos });

			uint64_t textureID = m_framebuffer->GetTextureID();
			ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });

			ImGui::End();
		}
	}

	ImVec2 GameViewportWindow::ResizeGameViewport()
	{
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		viewportPanelSize.x -= ImGui::GetScrollX();
		viewportPanelSize.y -= ImGui::GetScrollY();
		Bambo::WindowManager* windowManager = Bambo::WindowManager::Get();
		uint32 width = windowManager->GetWindowWidth();
		uint32 height = windowManager->GetWindowHeight();

		if (m_framebuffer->GetCurrentTextureWidth() != width || m_framebuffer->GetCurrentTextureHeight() != height)
		{
			m_framebuffer->Resize(width, height);
		}

		if (width > height)
		{
			float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
			viewportPanelSize.x = viewportPanelSize.y * aspectRatio;
		}
		else
		{
			float aspectRatio = static_cast<float>(height) / static_cast<float>(width);
			viewportPanelSize.y = viewportPanelSize.x * aspectRatio;
		}

		return viewportPanelSize;
	}

}