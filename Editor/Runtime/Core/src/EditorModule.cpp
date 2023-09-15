#include "EditorModule.h"
#include "EditorStates/MainEditorState.h"
#include "EditorStates/OpenProjectEditorState.h"
#include "InspectorDrawersRegistry.h"
#include "DefaultDrawers.h"
#include "EditorPaths.h"

namespace BamboEditor
{
	EditorModule::EditorModule(Bambo::Window* targetWindow) :
		m_editorContext(),
		m_states(),
		m_guiWorld(targetWindow)
	{}

	void EditorModule::OnAttach()
	{
		m_guiWorld.Initialize();

		m_editorContext.CurrentProject = std::make_unique<Project>();

		m_states.AddState(std::make_shared<OpenProjectEditorState>(&m_editorContext, &m_states));
		m_states.AddState(std::make_shared<MainEditorState>(&m_editorContext));

		InspectorDrawersRegistry* drawerRegistry = SingletonManager::Get()->Register<InspectorDrawersRegistry>();
		drawerRegistry->Register(SpriteComponent::GetTypeID(), DrawSpriteComponent);
		drawerRegistry->Register(CameraComponent::GetTypeID(), DrawCameraComponent);

		m_states.EnterTo(static_cast<uint32>(EditorStateType::OpenProject));
	}

	void EditorModule::OnDetach()
	{
		m_states.Clear();
		m_guiWorld.Dispose();
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

	void EditorModule::OnGUIStart()
	{
		m_guiWorld.StartFrame();
	}

	void EditorModule::OnGUI()
	{
		IEditorState* editorState = m_states.GetCurrentState();
		if (!editorState) return;
		editorState->OnGUI();
	}

	void EditorModule::OnGUIEnd()
	{
		m_guiWorld.EndFrame();
	}
}