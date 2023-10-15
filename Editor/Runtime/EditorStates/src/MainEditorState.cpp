#include "MainEditorState.h"
#include "SceneHierarchy.h"
#include "ContentBrowser.h"
#include "GameViewport.h"
#include "Inspector.h"
#include "BamboPaths.h"
#include "RenderManager.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"

namespace BamboEditor
{
	MainEditorState::MainEditorState(EditorContext* editorContext) :
		m_editorContext(editorContext)
	{}

	void MainEditorState::Enter()
	{
		BAMBO_ASSERT_S(m_editorContext)
		BAMBO_ASSERT_S(m_editorContext->CurrentProject)
		BAMBO_ASSERT_S(!m_editorContext->CurrentWorld)

		Bambo::WindowManager* windowManager = m_editorContext->Engine->GetWindowManager();
		Bambo::RenderManager* renderManager = m_editorContext->Engine->GetRenderManager();
		uint32 width = windowManager->GetWindowWidth();
		uint32 height = windowManager->GetWindowHeight();
		m_framebuffer = Bambo::Framebuffer::Create(renderManager->GetCurrentRenderAPI(), { Bambo::FramebufferTextureType::Color }, width, height);

		m_windows.emplace_back<UPtr<SceneHierarchyWindow>>(std::make_unique<SceneHierarchyWindow>(m_editorContext));
		m_windows.emplace_back<UPtr<ContentBrowserWindow>>(std::make_unique<ContentBrowserWindow>(m_editorContext));
		m_windows.emplace_back<UPtr<InspectorWindow>>(std::make_unique<InspectorWindow>(m_editorContext));
		m_windows.emplace_back<UPtr<GameViewportWindow>>(std::make_unique<GameViewportWindow>(m_editorContext, m_framebuffer));

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;

		m_editorContext->Engine->GetResourceManager()->ScanFiles(m_editorContext->CurrentProject->GetAssetsPath());
		OpenWorld(m_editorContext->CurrentProject->GetStartupWorldPath());
	}

	void MainEditorState::Exit()
	{
		m_editorContext->CurrentWorld.reset();
		m_framebuffer.reset();
		m_windows.clear();
	}

	void MainEditorState::OnUpdate(float deltaTime) 
	{
		if (m_editorContext->EditorCamera)
		{
			m_editorContext->EditorCamera->Tick(deltaTime);
		}
	}

	void MainEditorState::OnRender()
	{
		Bambo::RenderManager* renderManager = m_editorContext->Engine->GetRenderManager();
		renderManager->GetRenderer()->Clear();

		m_framebuffer->Bind();

		renderManager->GetRenderer()->Clear();

		//@TODO: Отрисовка сетки?

		if (m_editorContext->CurrentWorld)
		{
			m_editorContext->CurrentWorld->Render();
		}

		m_framebuffer->Unbind();
	}

	void MainEditorState::OnGUI()
	{
		bool isToolActive = true;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGuiID mainWindowId = ImGui::DockSpaceOverViewport(viewport, ImGuiDockNodeFlags_PassthruCentralNode);
		

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save")) { SaveProject(); }
				if (ImGui::MenuItem("Close")) { isToolActive = false; }
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		for (UPtr<GUIWindow>& window : m_windows)
		{
			window->OnGUI();
		}
	}

	void MainEditorState::OpenWorld(const std::filesystem::path& worldPath)
	{
		Bambo::WorldContext parameters{};
		parameters.AssetsFolderPath = m_editorContext->CurrentProject->GetAssetsPath();
		parameters.WorldFilePath = worldPath;
		parameters.Engine = m_editorContext->Engine;

		m_editorContext->CurrentWorld = std::make_shared<Bambo::World>(parameters);
		Bambo::GameObject* editorCamera = m_editorContext->CurrentWorld->CreateGameObject();
		editorCamera->AddProperty(Bambo::GameObject::IsEditorOnly);
		m_editorContext->EditorCamera = editorCamera->AddComponent<EditorCamera>();
	}

	void MainEditorState::SaveProject()
	{
		BAMBO_ASSERT_S(m_editorContext)
		BAMBO_ASSERT_S(m_editorContext->CurrentProject)
		BAMBO_ASSERT_S(m_editorContext->CurrentWorld)

		m_editorContext->CurrentProject->SaveProject();
		m_editorContext->CurrentWorld->SaveWorld();
	}
}