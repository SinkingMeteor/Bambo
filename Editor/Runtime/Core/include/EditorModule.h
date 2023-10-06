#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"
#include "Module.h"
#include "Project.h"
#include "EditorPaths.h"
#include "Patterns/StateMachine.h"
#include "EditorStates/IEditorState.h"
#include "EditorContext.h"
#include "EditorGUIContext.h"
#include "Engine.h"

namespace BamboEditor
{
	class EditorModule : public Bambo::Module
	{
	public:
		EditorModule();
		virtual int32 GetModuleName() const override { return 'EDTM'; }
		virtual void OnAttach(Bambo::Engine* engine) override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float deltaTIme) override;
		virtual void OnRender() override;
		virtual void OnGUIStart() override;
		virtual void OnGUIEnd() override;
		virtual void OnGUI() override;
	private:
		EditorContext m_editorContext;
		EditorConfig m_editorConfig;

		Bambo::StateMachine<IEditorState> m_states;
		EditorGUIContext m_guiWorld;

		void LoadEditorConfig();
		void SaveEditorConfig();
	};
}