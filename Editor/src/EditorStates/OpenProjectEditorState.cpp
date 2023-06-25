#include "EditorStates/OpenProjectEditorState.h"

namespace BamboEditor
{
	OpenProjectEditorState::OpenProjectEditorState(SPtr<Project> project) :
		m_currentProject(project)
	{}

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
	}

	void OpenProjectEditorState::OnEvent(Bambo::Event& event)
	{
	}
}