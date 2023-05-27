#pragma once
#include "imgui.h"
#include "Main/Module.h"
#include "World/World.h"
#include "EngineEvent.h"
#include "RenderManager.h"
#include <fstream>
#include "Project.h"
#include "EditorPaths.h"

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
		virtual void OnGUI() override;
		virtual void OnEvent(Bambo::Event& event) override;
	private:
		UPtr<Project> m_currentProject;
		UPtr<Bambo::World> m_currentWorld;

		void OpenWorld();
		void OpenWorld(const std::string& worldFilePath) {};
	};
}