#pragma once
#include "Essentials.h"
#include "Module.h"
#include "Project.h"
#include "EditorPaths.h"
#include "Patterns/StateMachine.h"
#include "EditorStates/IEditorState.h"
#include "EditorContext.h"
#include "EditorGUIContext.h"

namespace BamboEditor
{
	class EditorModule : public Bambo::Module
	{
	public:
		EditorModule(Bambo::Window* targetWindow);
		virtual int32 GetModuleName() const override { return 'EDTM'; }
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float deltaTIme) override;
		virtual void OnRender() override;
		virtual void OnGUIStart() override;
		virtual void OnGUIEnd() override;
		virtual void OnGUI() override;
	private:
		EditorContext m_editorContext;
		Bambo::StateMachine<IEditorState> m_states;
		EditorGUIContext m_guiWorld;
	};
}