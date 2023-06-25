#pragma once
#include "Essentials.h"
#include "EditorStates/IEditorState.h"
#include "Project.h"
namespace BamboEditor
{
	class OpenProjectEditorState final : public IEditorState
	{
	public:
		OpenProjectEditorState(SPtr<Project> project);
		virtual uint32 GetId() const override { return static_cast<uint32>(EditorStateType::OpenProject); };
		virtual void Enter() override;
		virtual void Exit() override;

		virtual void OnUpdate(float deltaTIme) override;
		virtual void OnRender() override;
		virtual void OnGUI() override;
		virtual void OnEvent(Bambo::Event& event) override;
	private:
		SPtr<Project> m_currentProject;
	};


}