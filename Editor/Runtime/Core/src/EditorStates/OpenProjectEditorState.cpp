#include "EditorStates/OpenProjectEditorState.h"

namespace
{
	DECLARE_LOG_CATEGORY_STATIC(OpenProjectEditorStateLog)
}

namespace BamboEditor
{

	OpenProjectEditorState::OpenProjectEditorState(EditorContext* editorContext, EditorConfig* editorConfig, Bambo::StateMachine<IEditorState>* stateMachine) :
		m_stateMachine(stateMachine),
		m_editorContext(editorContext),
		m_editorConfig(editorConfig),
		m_browserWindow()
	{
		m_browserWindow = std::make_unique<ProjectBrowserWindow>(editorContext, std::bind(&OpenProjectEditorState::OpenEditor, this));
	}

	void OpenProjectEditorState::Enter()
	{
	}

	void OpenProjectEditorState::Exit()
	{
	}

	void OpenProjectEditorState::OnUpdate(float deltaTIme)
	{
	}

	void OpenProjectEditorState::OnRender()
	{
	}

	void OpenProjectEditorState::OnGUI()
	{
		ImGuiViewport* viewport = ImGui::GetWindowViewport();

		ImGui::SetNextWindowPos({ 0.0f, 0.0f });
		ImGui::SetNextWindowSize({ viewport->Size.x, viewport->Size.y * 0.5f });
		ImGui::Begin("OpenRecentWindow", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
		
		for (int i = 0; i < m_editorConfig->Projects.size(); ++i)
		{
			std::string& projectFilePath = m_editorConfig->Projects[i];

			if (ImGui::Button(projectFilePath.c_str(), { viewport->Size.x, 0}))
			{
				if (!m_editorContext->CurrentProject->OpenProject(projectFilePath))
				{
					Bambo::Logger::Get()->Log(OpenProjectEditorStateLog, Bambo::Verbosity::Error, "Can't open the project file.");
					continue;
				}

				OpenEditor();
				break;
			}
		} 

		ImGui::End();

		ImGui::SetNextWindowPos({0.0f, viewport->Size.y * 0.5f});
		ImGui::SetNextWindowSize({ viewport->Size.x, viewport->Size.y * 0.5f });
		m_browserWindow->OnGUI();
	}

	void OpenProjectEditorState::OpenEditor()
	{
		const std::filesystem::path& currentProjectPath = m_editorContext->CurrentProject->GetRootPath();

		bool wasFound = false;
		for (int i = 0; i < m_editorConfig->Projects.size(); ++i)
		{
			std::string& projectFilePath = m_editorConfig->Projects[i];

			if (projectFilePath == currentProjectPath)
			{
				wasFound = true;
				break;
			}
		}

		if (!wasFound)
		{
			m_editorConfig->Projects.push_back(currentProjectPath.string());
		}

		BAMBO_ASSERT_S(m_stateMachine)
		m_stateMachine->EnterTo(static_cast<uint32>(EditorStateType::Main));
	}
}