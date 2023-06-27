#include "EditorStates/MainEditorState.h"
#include "Windows/SceneHierarchy.h"
#include "Windows/ContentBrowser.h"
#include "Windows/GameViewport.h"
#include "RenderManager.h"

namespace BamboEditor
{
	MainEditorState::MainEditorState(SPtr<Project> project) :
		m_currentProject(project)
	{
		Bambo::WindowManager* windowManager = Bambo::WindowManager::Get();
		uint32 width = windowManager->GetWindowWidth();
		uint32 height = windowManager->GetWindowHeight();
		m_framebuffer = Bambo::Framebuffer::Create({ Bambo::FramebufferTextureType::Color }, width, height);

		m_currentWorld = std::make_shared<Bambo::World>();
		m_windows.emplace_back<UPtr<SceneHierarchyWindow>>(std::make_unique<SceneHierarchyWindow>(m_currentWorld));
		m_windows.emplace_back<UPtr<ContentBrowserWindow>>(std::make_unique<ContentBrowserWindow>());
		m_windows.emplace_back<UPtr<GameViewportWindow>>(std::make_unique<GameViewportWindow>(m_framebuffer));

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
	}

	void MainEditorState::Enter()
	{
		OpenWorld(m_currentProject->GetStartupWorldPath());
		DispatchNewProject();
	}

	void MainEditorState::Exit()
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}
	}

	void MainEditorState::OnUpdate(float deltaTime)
	{
		if (m_currentWorld)
		{
			m_currentWorld->Update(deltaTime);
		}
	}

	void MainEditorState::OnRender()
	{
		Bambo::RenderManager* renderManager = Bambo::RenderManager::Get();
		renderManager->GetRenderer().Clear();

		m_framebuffer->Bind();

		renderManager->GetRenderer().Clear();

		if (m_currentWorld)
		{
			m_currentWorld->Render();
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
				if (ImGui::MenuItem("Save", "Ctrl+S")) { m_currentProject->SaveProject(); }
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

	void MainEditorState::OnEvent(Bambo::Event& event)
	{
	}

	void MainEditorState::OpenWorld(const std::filesystem::path& worldPath)
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}
		m_currentWorld->Initialize();

		if (worldPath.empty()) return;
	}

	void MainEditorState::SaveProject()
	{

	}

	void MainEditorState::DispatchNewProject()
	{
		for (size_t i = 0; i < m_windows.size(); ++i)
		{
			m_windows[i]->OnProjectChanged(*m_currentProject);
		}
	}

}