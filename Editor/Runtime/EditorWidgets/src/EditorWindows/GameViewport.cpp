#include "EditorWindows/GameViewport.h"
#include "RenderManager.h"

namespace BamboEditor
{
	GameViewportWindow::GameViewportWindow(SPtr<Bambo::Framebuffer> framebuffer) :
		m_framebuffer(framebuffer),
		m_windowName("Game viewport"),
		m_isOpenedInfoPanel(false)
	{}

	void GameViewportWindow::OnGUI()
	{
		ImGui::Begin("Game Viewport", nullptr,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse);

		DrawMenuBar();

		ImVec2 viewportPanelSize = ResizeGameViewport();
		ImVec2 windowSize = ImGui::GetWindowSize();
		float xPos = (windowSize.x - viewportPanelSize.x) * 0.5f;
		float yPos = (windowSize.y - viewportPanelSize.y) * 0.5f;
		ImGui::SetCursorPos(ImVec2{ xPos, yPos });

		uint64_t textureID = m_framebuffer->GetTextureID();
		ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });

		ImGui::End();

		DrawInfoOverlay();

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

	void GameViewportWindow::DrawMenuBar()
	{
		Bambo::RenderParameters& renderParameters = Bambo::RenderManager::Get()->GetRenderParameters();

		if (ImGui::BeginMenuBar())
		{
			ImGui::Checkbox("Info", &m_isOpenedInfoPanel);
			ImGui::Checkbox("Draw debug", &renderParameters.DrawDebug);
			ImGui::EndMenuBar();
		}
	}

	void GameViewportWindow::DrawInfoOverlay()
	{
		if (!m_isOpenedInfoPanel) return;

		ImGuiIO& io = ImGui::GetIO();
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoNav;
		
		ImVec2 windowPosition = ImGui::GetWindowPos();
		windowPosition.x += 50.0f;
		windowPosition.y += 50.0f;

		ImGui::SetNextWindowPos(windowPosition, ImGuiCond_Always, ImVec2(0.0f, 0.0f));

		ImGui::SetNextWindowBgAlpha(0.35f); 
		if (ImGui::Begin("Game Viewport info", nullptr, window_flags))
		{
			ImGui::Text("Viewport info:");
			ImGui::Separator();

			float deltaTime = Bambo::TimeManager::Get()->GetLastDeltaTime();
			int32 fps = static_cast<int32>(1.0f / deltaTime);

			Bambo::RenderStatistics& renderStatistics = Bambo::RenderManager::Get()->GetRenderStatistics();

			ImGui::Text("FPS: %i", fps);
			ImGui::Text("Draw calls: %i", renderStatistics.DrawCalls);
			ImGui::Text("Saved by batching: %i", renderStatistics.SavedByBatching);
			ImGui::End();
		}
	}
}