#pragma once
#include "imgui.h"
#include "Main/Module.h"
#include "World/World.h"
#include "EngineEvent.h"
#include "RenderManager.h"
#include <fstream>
#include "Project.h"
#include "EditorPaths.h"
#include "Windows/SceneHierarchy.h"
#include "Windows/GameViewport.h"
#include "Framebuffer.h"

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
		UPtr<Project> m_currentProject;
		SPtr<Bambo::World> m_currentWorld;
		std::vector<UPtr<GUIWindow>> m_windows;
		SPtr<Bambo::Framebuffer> m_framebuffer;

		void OpenWorld();
		void OpenWorld(const std::string& worldFilePath) {};
	};
}