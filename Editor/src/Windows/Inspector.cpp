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

		if (!m_editorContext->SelectedGameObject || !m_editorContext->SelectedGameObject.IsValid())
		{
			ImGui::End();
			return;
		}

		Bambo::GameObject* gameObject = m_editorContext->CurrentWorld->GetGameObject(m_editorContext->SelectedGameObject);

		std::string& name = gameObject->GetName();
		DrawString("Name", &name);

		DrawTransformComponent(gameObject->GetTransform());
		InspectorDrawersRegistry* drawersRegistry = InspectorDrawersRegistry::Get();

		std::vector<UPtr<Bambo::Component>>& components = gameObject->GetComponentsArray();

		for (size_t i = 0; i < components.size(); ++i)
		{
			drawersRegistry->DrawComponent(components[i]->GetID(), components[i].get());
		}

		ImGui::End();
	}
}