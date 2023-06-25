#include "EditorModule.h"
#include "EditorStates/MainEditorState.h"
#include "EditorStates/OpenProjectEditorState.h"
namespace BamboEditor
{
	void EditorModule::OnAttach()
	{
		m_currentProject = std::make_unique<Project>();
		m_currentProject->CreateDefaultProject();

		m_states.AddState(std::make_shared<OpenProjectEditorState>(m_currentProject));
		m_states.AddState(std::make_shared<MainEditorState>(m_currentProject));

		m_states.EnterTo(static_cast<uint32>(EditorStateType::Main));
	}

	void EditorModule::OnDetach()
	{
		m_states.Clear();
	}

	void EditorModule::OnUpdate(float deltaTime)
	{
		IEditorState* editorState = m_states.GetCurrentState();
		if (!editorState) return;
		editorState->OnUpdate(deltaTime);
	}
	
	void EditorModule::OnRender()
	{
		IEditorState* editorState = m_states.GetCurrentState();
		if (!editorState) return;
		editorState->OnRender();
	}

	void EditorModule::OnGUI()
	{
		IEditorState* editorState = m_states.GetCurrentState();
		if (!editorState) return;
		editorState->OnGUI();
	}

	void EditorModule::OnEvent(Bambo::Event& event)
	{
		IEditorState* editorState = m_states.GetCurrentState();
		if (!editorState) return;
		editorState->OnEvent(event);
	}

}