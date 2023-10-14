#include "Inspector.h"
#include "InspectorDrawersRegistry.h"
#include "EditorModule.h"
namespace BamboEditor
{
	InspectorWindow::InspectorWindow(EditorContext* editorContext) :
		m_windowName("Inspector"),
		m_editorContext(editorContext),
		m_internalData()
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

		bool isObjectDisabled = gameObject->HasProperty(Bambo::GameObject::IsDisabled);
		std::string& label = isObjectDisabled ? m_internalData.DisabledGameObjectLabel : m_internalData.EnabledGameObjectLabel;

		if (ImGui::Button(label.c_str()))
		{
			if (isObjectDisabled)
			{
				gameObject->RemoveProperty(Bambo::GameObject::IsDisabled);
			}
			else
			{
				gameObject->AddProperty(Bambo::GameObject::IsDisabled);
			}
		}

		std::string& name = gameObject->GetName();
		DrawString("GameObject: ", &name);

		DrawTransformComponent(gameObject->GetTransform());
		InspectorDrawersRegistry* drawersRegistry = m_editorContext->Editor->GetDrawersRegistry();

		std::vector<UPtr<Bambo::Component>>& components = gameObject->GetComponentsArray();

		for (size_t i = 0; i < components.size(); ++i)
		{
			DrawReadonlyString(&components[i]->GetName());

			if (drawersRegistry->IsRegistered(components[i]->GetID()))
			{
				drawersRegistry->DrawComponent(components[i]->GetID(), components[i].get());
			}
		}

		ImGui::End();
	}
}