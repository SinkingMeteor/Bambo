#include "EditorModule.h"

namespace BamboEditor
{
	void EditorModule::OnAttach()
	{
		OpenWorld();
	}

	void EditorModule::OnDetach()
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}
	}

	void EditorModule::OnUpdate(float deltaTIme)
	{
		Bambo::RenderManager* renderManager = Bambo::RenderManager::Get();
		renderManager->GetRenderer().Clear();
	}
	
	void EditorModule::OnGUI()
	{
		ImGui::ShowDemoWindow();
	}

	void EditorModule::OnEvent(Bambo::Event& event)
	{

	}

	void EditorModule::OpenWorld()
	{
		if (m_currentWorld)
		{
			m_currentWorld->Dispose();
		}

		m_currentWorld = std::make_unique<Bambo::World>();
		m_currentWorld->Initialize();
	}

}