#include "Windows/SceneHierarchy.h"

namespace BamboEditor
{
	SceneHierarchyWindow::SceneHierarchyWindow(EditorContext* editorContext) :
		m_windowName("Hierarchy"),
		m_editorContext(editorContext),
		m_selectedGameObject(nullptr)
	{}

	void SceneHierarchyWindow::OnGUI()
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysVerticalScrollbar;

		ImGui::Begin(m_windowName.c_str(), nullptr, flags);

		if (!m_editorContext || !m_editorContext->CurrentWorld)
		{
			ImGui::End();
			return;
		}

		if (ImGui::IsItemClicked())
		{
			m_selectedGameObject = nullptr;
		}

		const Bambo::GameObject* rootGo = m_editorContext->CurrentWorld->GetRoot();

		static ImGuiTableFlags tableFlags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
		if (ImGui::BeginTable("SceneHierarchy", 1, tableFlags))
		{
			ImGui::TableSetupColumn("Hierarchy", ImGuiBackendFlags_None);
			ImGui::TableHeadersRow();

			DisplayChildrenOf(rootGo);
			ImGui::EndTable();
		}

		ImGui::SetNextWindowSize({ 200.0f, 200.0f });
		
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::TreeNode("Add"))
			{
				if (ImGui::MenuItem("Empty")) { CreateEmpty(); }
				if (ImGui::MenuItem("Camera")) { CreateCamera(); }
				ImGui::TreePop();
			}
			ImGui::EndPopup();
		}

		ImGui::End();
	}

	Bambo::GameObject* SceneHierarchyWindow::CreateEmpty()
	{
		return m_editorContext->CurrentWorld->CreateGameObject(m_selectedGameObject);
	}

	void SceneHierarchyWindow::CreateCamera()
	{
		CreateEmpty()->AddComponent<Bambo::CameraComponent>();
	}

	void SceneHierarchyWindow::DisplayChildrenOf(const Bambo::GameObject* gameObject, ImGuiTreeNodeFlags additionalFlags)
	{
		const Bambo::RelationshipComponent* relComp = gameObject->GetComponentConst<Bambo::RelationshipComponent>();
		const std::vector<Bambo::RelationshipComponent*>& children = relComp->GetChildrenConst();

		for (int i = 0; i < children.size(); ++i)
		{
			Bambo::GameObject* childGo = children[i]->GetOwner();
			Bambo::RelationshipComponent* childRelComp = childGo->GetComponent<Bambo::RelationshipComponent>();

			BAMBO_ASSERT_S(childGo)
			BAMBO_ASSERT_S(childGo->IsValid())
			BAMBO_ASSERT_S(childGo->HasComponent<Bambo::TagComponent>())

			Bambo::IID id = childGo->GetID();
			const Bambo::TagComponent* tag = childGo->GetComponentConst<Bambo::TagComponent>();

			const static ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
			ImGuiTreeNodeFlags nodeFlags = baseFlags | additionalFlags;

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			if (ImGui::TreeNodeEx((void*)(uintptr_t)id, nodeFlags, tag->Tag.c_str()))
			{
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					//@TODO: To inspector window
					m_selectedGameObject = m_editorContext->CurrentWorld->GetGameObject(id);
				}

				if (ImGui::BeginDragDropSource())
				{
					ImGui::SetDragDropPayload("GOReparent", &*childGo, sizeof(*childGo));
					ImGui::Text("%s", tag->Tag.c_str());
					ImGui::EndDragDropSource();
				}

				if (ImGui::BeginDragDropTarget())
				{
						const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GOReparent");
						if(payload != nullptr)
						{
							Bambo::GameObject* targetGo = static_cast<Bambo::GameObject*>(payload->Data);
							targetGo->GetComponent<Bambo::RelationshipComponent>()->SetParent(childRelComp);
						}

						ImGui::EndDragDropTarget();
				}

				bool noChildren = childRelComp->GetChildrenCount() == 0;
				DisplayChildrenOf(childGo, noChildren ? (ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet) : ImGuiBackendFlags_None);
				ImGui::TreePop();
			}
		}
	}

}