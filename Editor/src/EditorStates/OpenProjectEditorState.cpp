#include "EditorStates/OpenProjectEditorState.h"
#include "Windows/ProjectBrowser.h"

namespace BamboEditor
{
	OpenProjectEditorState::OpenProjectEditorState(EditorContext* editorContext, Bambo::StateMachine<IEditorState>* stateMachine) :
		m_stateMachine(stateMachine),
		m_editorContext(editorContext),
		m_windows()
	{
		m_windows.emplace_back<UPtr<ProjectBrowserWindow>>(std::make_unique<ProjectBrowserWindow>(editorContext, std::bind(&OpenProjectEditorState::OpenEditor, this)));

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags &= ~ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
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
		for (UPtr<GUIWindow>& window : m_windows)
		{
			window->OnGUI();
		}
	}

	void OpenProjectEditorState::OpenEditor()
	{
		BAMBO_ASSERT_S(m_stateMachine)
		m_stateMachine->EnterTo(static_cast<uint32>(EditorStateType::Main));
	}
}