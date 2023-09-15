#pragma once
#include "Essentials.h"
#include "EditorStates/IEditorState.h"
#include "Patterns/StateMachine.h"
#include "Project.h"
#include "EditorWindows/GUIWindow.h"
#include "EditorContext.h"
namespace BamboEditor
{
	class OpenProjectEditorState final : public IEditorState
	{
	public:
		OpenProjectEditorState(EditorContext* editorContext, Bambo::StateMachine<IEditorState>* stateMachine);
		virtual uint32 GetId() const override { return static_cast<uint32>(EditorStateType::OpenProject); };
		virtual void Enter() override;
		virtual void Exit() override;

		virtual void OnUpdate(float deltaTIme) override;
		virtual void OnRender() override;
		virtual void OnGUI() override;

	private:
		Bambo::StateMachine<IEditorState>* m_stateMachine;
		EditorContext* m_editorContext;
		std::vector<UPtr<GUIWindow>> m_windows;

		void OpenEditor();
	};


}