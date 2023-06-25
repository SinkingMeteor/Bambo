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
		std::ifstream editorConfigiStream{ BamboPaths::BamboEditorConfigDir };
		nlohmann::json rootConfig{};

		if (editorConfigiStream.fail())
		{
			Bambo::Logger::Get()->Log("LogEditorModule", Bambo::Verbosity::Fatal, "Can't open or find editor config file. Please check EditorConfig.json file at root folder");
		}
		else
		{
			rootConfig << editorConfigiStream;
		}

		if (rootConfig["CurrentProjectFolderPath"].is_null())
		{
			Bambo::Logger::Get()->Log("LogEditorModule", Bambo::Verbosity::Error, "Editor config file doesn't contains current project folder path. Please add \"CurrentProjectFolderPath\" or reassembly editor");
			rootConfig["CurrentProjectFolderPath"] = std::string{};
		}

		if (rootConfig["CurrentProjectName"].is_null())
		{
			Bambo::Logger::Get()->Log("LogEditorModule", Bambo::Verbosity::Error, "Editor config file doesn't contains current project name. Please add \"CurrentProjectName\" or reassembly editor");
			rootConfig["CurrentProjectName"] = std::string{};
		}

		std::filesystem::path currentProjectPath{ rootConfig["CurrentProjectFolderPath"].get<std::string>() };
		std::string currentProjectName = rootConfig["CurrentProjectName"];

		m_currentProject->LoadProject(currentProjectPath, currentProjectName);

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