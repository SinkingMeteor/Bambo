#include "Windows/Inspector.h"
#include "Drawers/InspectorDrawersRegistry.h"
namespace BamboEditor
{
	InspectorWindow::InspectorWindow(EditorContext* editorContext) :
		m_windowName("Inspector"),
		m_editorContext(editorContext)
	{}
	
	void InspectorWindow::OnGUI()
	{
		ImGui::Begin("Inspector", nullptr,
			ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar |
			ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse);

		if (!m_editorContext->SelectedGameObject || !m_editorContext->SelectedGameObject->IsValid())
		{
			ImGui::End();
			return;
		}

		std::string& name = m_editorContext->SelectedGameObject->GetName();
		DrawString("Name", &name);

		DrawTransformComponent(m_editorContext->SelectedGameObject->GetTransform());
		InspectorDrawersRegistry* drawersRegistry = InspectorDrawersRegistry::Get();

		std::vector<UPtr<Bambo::Component>>& components = m_editorContext->SelectedGameObject->GetComponentsArray();

		for (size_t i = 0; i < components.size(); ++i)
		{
			drawersRegistry->DrawComponent(components[i]->GetID(), components[i].get());
		}

		ImGui::End();
	}
}