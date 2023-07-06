#include "EditorModule.h"
#include "EditorStates/MainEditorState.h"
#include "EditorStates/OpenProjectEditorState.h"
#include "EditorPaths.h"

namespace BamboEditor
{
	void EditorModule::OnAttach()
	{
		Bambo::TextureProvider* textureProvider = Bambo::TextureProvider::Get();
		textureProvider->Load(Bambo::ToId(BamboPaths::FILE_ICON_TEXTURE_KEY), BamboPaths::BamboEditorResourceDir + "Graphics/EditorFileIcon.jpg");
		textureProvider->Load(Bambo::ToId(BamboPaths::FOLDER_ICON_TEXTURE_KEY), BamboPaths::BamboEditorResourceDir + "Graphics/EditorFolderIcon.png");

		m_editorContext.CurrentProject = std::make_unique<Project>();

		m_states.AddState(std::make_shared<OpenProjectEditorState>(&m_editorContext, &m_states));
		m_states.AddState(std::make_shared<MainEditorState>(&m_editorContext));

		m_states.EnterTo(static_cast<uint32>(EditorStateType::OpenProject));
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
}