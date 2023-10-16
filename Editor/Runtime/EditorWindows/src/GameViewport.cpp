#include "GameViewport.h"
#include "RenderManager.h"
#include "EditorContext.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"

namespace BamboEditor
{
	GameViewportWindow::GameViewportWindow(EditorContext* editorContext, SPtr<Bambo::Framebuffer> framebuffer) :
		m_windowName("Game viewport"),
		m_framebuffer(framebuffer),
		m_editorContext(editorContext),
		m_mouseScrollFactor(0.5f),
		m_isOpenedInfoPanel(false)
	{}

	void GameViewportWindow::OnGUI()
	{
		ImGui::Begin("Game Viewport", nullptr,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse);

		DrawMenuBar();
		ProcessCameraMovement();

		ImVec2 viewportPanelSize = ResizeGameViewport();
		ImVec2 windowSize = ImGui::GetWindowSize();
		float xPos = (windowSize.x - viewportPanelSize.x) * 0.5f;
		float yPos = (windowSize.y - viewportPanelSize.y) * 0.5f;
		ImGui::SetCursorPos(ImVec2{ xPos, yPos });

		uint64_t textureID = m_framebuffer->GetTextureID();
		ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2{ 0.0f, 1.0f }, ImVec2{ 1.0f, 0.0f });

		if (m_editorContext->SelectedGameObject.IsValid())
		{
			Bambo::GameObject* root = m_editorContext->CurrentWorld->GetRoot();
			glm::mat4& rootMatrix = root->GetTransform()->GetMatrix();
			glm::mat4 inversedRootMatrix = glm::inverse(rootMatrix);

			Bambo::GameObject* selectedObj = m_editorContext->CurrentWorld->GetGameObject(m_editorContext->SelectedGameObject);
			glm::vec3 pos = selectedObj->GetTransform()->GetGlobalPosition();

			Bambo::DrawDebugRhombus(m_editorContext->CurrentWorld.get(), Bambo::Vector3f{ pos.x, pos.y, pos.z }, 10.0f, Bambo::Color::Cyan(), 3.0f);
		}


		ImGui::End();

		DrawInfoOverlay();

	}

	void GameViewportWindow::ProcessCameraMovement()
	{
		if (!m_editorContext->EditorCamera) return;

		bool isFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
		m_editorContext->EditorCamera->SetMovementEnabled(isFocused);

		if (ImGui::IsMouseDown(ImGuiMouseButton_Right))
		{
			ImVec2 delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);

			Bambo::Transform* transform = m_editorContext->EditorCamera->GetOwner()->GetTransform();
			transform->AddToPosition({ delta.x * 0.04f * m_mouseScrollFactor, -delta.y * 0.04f * m_mouseScrollFactor, 0.0f });
		}
	}

	ImVec2 GameViewportWindow::ResizeGameViewport()
	{
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		viewportPanelSize.x -= ImGui::GetScrollX();
		viewportPanelSize.y -= ImGui::GetScrollY();
		Bambo::WindowManager* windowManager = m_editorContext->Engine->GetWindowManager();

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
		Bambo::RenderParameters& renderParameters = m_editorContext->Engine->GetRenderManager()->GetRenderParameters();

		if (ImGui::BeginMenuBar())
		{
			ImGui::Checkbox("Info", &m_isOpenedInfoPanel);
			ImGui::Checkbox("Draw debug", &renderParameters.DrawDebug);

			ImGui::SetNextItemWidth(80.0f);
			ImGui::SliderFloat("Scroll speed", &m_mouseScrollFactor, 0.1f, 2.0f);

			if (m_editorContext->EditorCamera)
			{
				ImGui::SetNextItemWidth(80.0f);
				ImGui::SliderFloat("Camera speed", &m_editorContext->EditorCamera->GetCameraSpeedRef(), 25.0f, 200.0f);
				if (ImGui::Button("Reset", ImVec2{ 60.0f, 0.0f }))
				{
					Bambo::Transform* transform = m_editorContext->EditorCamera->GetOwner()->GetTransform();
					float zPos = transform->GetPosition().z;
					transform->SetPosition(glm::vec3{ 0.0f, 0.0f, zPos });
				}
			}

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

			float deltaTime = m_editorContext->Engine->GetTimeManager()->GetLastDeltaTime();
			int32 fps = static_cast<int32>(1.0f / deltaTime);

			Bambo::RenderStatistics& renderStatistics = m_editorContext->Engine->GetRenderManager()->GetRenderStatistics();

			ImGui::Text("FPS: %i", fps);
			ImGui::Text("Draw calls: %i", renderStatistics.DrawCalls);
			ImGui::Text("Saved by batching: %i", renderStatistics.SavedByBatching);
			ImGui::End();
		}
	}
}