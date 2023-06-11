#include "EditorModule.h"

namespace BamboEditor
{
	void EditorModule::OnAttach()
	{
		m_currentProject = std::make_unique<Project>();
		m_currentProject->CreateDefaultProject();

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

		std::ifstream editorConfigiStream{ BamboPaths::BamboEditorConfigDir };
		if (!editorConfigiStream.fail())
		{
			nlohmann::json rootConfig{};
			rootConfig << editorConfigiStream;
			BAMBO_ASSERT_S(!rootConfig.is_null())

				//TODO: Вывести список доступных проектов

			std::string currentProjectPath = rootConfig["CurrentProjectPath"];
			m_currentProject->LoadProject(currentProjectPath);
		}
		
		OpenWorld(m_currentProject->GetStartupWorldPath());
		DispatchNewProject();
	}

	void EditorModule::OnDetach()
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}
	}

	void EditorModule::OnUpdate(float deltaTime)
	{
		if (m_currentWorld)
		{
			m_currentWorld->Update(deltaTime);
		}
	}
	
	void EditorModule::OnRender()
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


	void EditorModule::OnGUI()
	{
		bool isToolActive = true;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::DockSpaceOverViewport(viewport, ImGuiDockNodeFlags_::ImGuiDockNodeFlags_PassthruCentralNode);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N")) { CreateProject(); }
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { OpenProject(); }
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

	void EditorModule::OnEvent(Bambo::Event& event)
	{

	}

	void EditorModule::OpenWorld(const std::filesystem::path& worldPath)
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}
		m_currentWorld->Initialize();
	
		if (worldPath.empty()) return;
	}

	void EditorModule::CreateProject()
	{
		DispatchNewProject();
	}

	void EditorModule::OpenProject()
	{
		DispatchNewProject();
	}

	void EditorModule::SaveProject()
	{

	}

	void EditorModule::DispatchNewProject()
	{
		for (size_t i = 0; i < m_windows.size(); ++i)
		{
			m_windows[i]->OnProjectChanged(*m_currentProject);
		}
	}

}