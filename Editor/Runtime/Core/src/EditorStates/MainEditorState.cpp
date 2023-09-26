#include "EditorStates/MainEditorState.h"
#include "EditorWindows/SceneHierarchy.h"
#include "EditorWindows/ContentBrowser.h"
#include "EditorWindows/GameViewport.h"
#include "EditorWindows/Inspector.h"
#include "BamboPaths.h"
#include "RenderManager.h"

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

		Bambo::WindowManager* windowManager = Bambo::WindowManager::Get();
		uint32 width = windowManager->GetWindowWidth();
		uint32 height = windowManager->GetWindowHeight();
		m_framebuffer = Bambo::Framebuffer::Create({ Bambo::FramebufferTextureType::Color }, width, height);

		m_windows.emplace_back<UPtr<SceneHierarchyWindow>>(std::make_unique<SceneHierarchyWindow>(m_editorContext));
		m_windows.emplace_back<UPtr<ContentBrowserWindow>>(std::make_unique<ContentBrowserWindow>(m_editorContext));
		m_windows.emplace_back<UPtr<InspectorWindow>>(std::make_unique<InspectorWindow>(m_editorContext));
		m_windows.emplace_back<UPtr<GameViewportWindow>>(std::make_unique<GameViewportWindow>(m_framebuffer));

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;

		ResourceManager::Get()->ScanFiles(m_editorContext->CurrentProject->GetAssetsPath());
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
		if (m_editorContext->CurrentWorld)
		{
			//@TODO: Depends on editor state

			//if editor state is play 
			//editorState->OnUpdate(deltaTime);
			//else
			//m_editorContext->CurrentWorld->Update(0);
		}
	}

	void MainEditorState::OnRender()
	{
		Bambo::RenderManager* renderManager = Bambo::RenderManager::Get();
		renderManager->GetRenderer()->Clear();

		m_framebuffer->Bind();

		renderManager->GetRenderer()->Clear();

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
		ImGui::DockSpaceOverViewport(viewport, ImGuiDockNodeFlags_::ImGuiDockNodeFlags_PassthruCentralNode);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save", "Ctrl+S")) { SaveProject(); }
				if (ImGui::MenuItem("Close", "Ctrl+W")) { isToolActive = false; }
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		for (UPtr<GUIWindow>& window : m_windows)
		{
			window->OnGUI();
		}

		ImGui::ShowDemoWindow();
	}

	void MainEditorState::OpenWorld(const std::filesystem::path& worldPath)
	{
		WorldParameters parameters{};
		parameters.AssetsFolderPath = m_editorContext->CurrentProject->GetAssetsPath();
		parameters.WorldFilePath = worldPath;

		m_editorContext->CurrentWorld = std::make_shared<Bambo::World>(parameters);
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