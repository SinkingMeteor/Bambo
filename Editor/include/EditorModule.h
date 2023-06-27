#pragma once
#include "Essentials.h"
#include "Main/Module.h"
#include "EngineEvent.h"
#include "Project.h"
#include "EditorPaths.h"
#include "Patterns/StateMachine.h"
#include "EditorStates/IEditorState.h"

namespace BamboEditor
{
	class EditorModule : public Bambo::Module
	{
	public:
		EditorModule() = default;
		virtual int32 GetModuleName() const override { return 'EDTM'; }
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(float deltaTIme) override;
		virtual void OnRender() override;
		virtual void OnGUI() override;
		virtual void OnEvent(Bambo::Event& event) override;
	private:
		SPtr<Project> m_currentProject;
		Bambo::StateMachine<IEditorState> m_states;
	};
}