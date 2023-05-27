#include "EditorModule.h"

namespace BamboEditor
{
	void EditorModule::OnAttach()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;

		//Загрузить config эдитора. В нем должны находиться все пути к проектам. Загрузить проект -> Загрузить мир

		std::ifstream editorConfigiStream{ BamboPaths::BamboEditorConfigDir };
		if (editorConfigiStream.fail())
		{
			//Проект-заглушка. В будущем заменить на диалоговое окно
			m_currentProject = std::make_unique<Project>("MockProject", "");
			OpenWorld();
			return;
		}

		nlohmann::json rootConfig{};
		rootConfig << editorConfigiStream;
		BAMBO_ASSERT_S(!rootConfig.is_null())

		//Вот тут, по идее, должен храниться список доступных проектов. Но пока он только один

		const std::string& projectName = rootConfig["CurrentProjectName"];
		const std::string& projectLocation = rootConfig["CurrentProjectLocation"];
		const std::string& projectFirstWorldPath = rootConfig["CurrentProjectFirstWorldPath"];
		
		m_currentProject = std::make_unique<Project>(projectName, projectLocation);
		m_currentProject->SetFirstWorldPath(projectFirstWorldPath);

		if (projectFirstWorldPath.size() == 0)
		{
			OpenWorld();
		}
		else
		{
			OpenWorld(projectFirstWorldPath);
		}

	}

	void EditorModule::OnDetach()
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}
	}

	void EditorModule::OnUpdate(float deltaTIme)
	{
		Bambo::RenderManager* renderManager = Bambo::RenderManager::Get();
		renderManager->GetRenderer().Clear();
	}
	
	void EditorModule::OnGUI()
	{
		bool isToolActive = true;

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
		ImVec2 appWindowSize = io.DisplaySize;
		ImVec2 menuBarSize{};

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::DockSpaceOverViewport(viewport);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) { isToolActive = false; }
				ImGui::EndMenu();
			}
			menuBarSize = ImGui::GetWindowSize();

			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("My First Tool", &isToolActive, ImGuiWindowFlags_MenuBar);
		ImGui::End();

		ImGui::ShowDemoWindow();
	}

	void EditorModule::OnEvent(Bambo::Event& event)
	{

	}

	void EditorModule::OpenWorld()
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}

		m_currentWorld = std::make_unique<Bambo::World>();
		m_currentWorld->Initialize();
	}

}