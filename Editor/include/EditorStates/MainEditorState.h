#pragma once
#include "Essentials.h"
#include "EditorStates/IEditorState.h"
#include "Project.h"
#include "World/World.h"
#include "Windows/GUIWindow.h"
#include "Framebuffer.h"

namespace BamboEditor
{
	class MainEditorState final : public IEditorState
	{
	public:
		MainEditorState(SPtr<Project> project);
		virtual uint32 GetId() const override { return static_cast<uint32>(EditorStateType::Main); };
		virtual void Enter() override;
		virtual void Exit() override;

		virtual void OnUpdate(float deltaTIme) override;
		virtual void OnRender() override;
		virtual void OnGUI() override;
		virtual void OnEvent(Bambo::Event& event) override;
	private:
		SPtr<Project> m_currentProject;
		SPtr<Bambo::World> m_currentWorld;
		std::vector<UPtr<GUIWindow>> m_windows;
		SPtr<Bambo::Framebuffer> m_framebuffer;

		void OpenWorld(const std::filesystem::path& worldFilePath);
		void SaveProject();
		void DispatchNewProject();
	};
}