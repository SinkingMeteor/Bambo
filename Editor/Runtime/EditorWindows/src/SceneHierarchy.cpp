#include "SceneHierarchy.h"

namespace
{
	Bambo::IID g_dragAndDroppedId;
}

namespace BamboEditor
{
	SceneHierarchyWindow::SceneHierarchyWindow(EditorContext* editorContext) :
		m_windowName("Hierarchy"),
		m_editorContext(editorContext),
		m_internalData()
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

		Bambo::WorldContext* worldContext = m_editorContext->CurrentWorld->GetWorldContext();
		BAMBO_ASSERT_S(worldContext)

		ImGui::Text(">> : %s", worldContext->WorldFilePath.filename().string().c_str());

		Bambo::IID previousSelected = m_editorContext->SelectedGameObject;

		const Bambo::GameObject* rootGo = m_editorContext->CurrentWorld->GetRoot();

		static ImGuiTableFlags tableFlags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
		if (ImGui::BeginTable("SceneHierarchy", 1, tableFlags))
		{
			ImGui::TableSetupColumn("Hierarchy", ImGuiBackendFlags_None);
			ImGui::TableHeadersRow();

			if (ImGui::BeginDragDropTarget())
			{
				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GOReparent");
				if (payload != nullptr)
				{
					Bambo::IID* goID = static_cast<Bambo::IID*>(payload->Data);
					Bambo::GameObject* targetGo = m_editorContext->CurrentWorld->GetGameObject(*goID);
					targetGo->SetParent(rootGo->GetID());
				}

				ImGui::EndDragDropTarget();
			}

			DisplayChildrenOf(rootGo, false);

			ImGui::EndTable();
		}


		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left) && previousSelected == m_editorContext->SelectedGameObject)
		{
			m_editorContext->SelectedGameObject = Bambo::IID{};
		}

		ImGui::SetNextWindowSize({ 200.0f, 200.0f });
		
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::TreeNode("Add"))
			{
				if (ImGui::MenuItem("Empty")) { CreateEmpty(); }
				if (ImGui::MenuItem("Sprite")) { CreateSprite(); }
				if (ImGui::MenuItem("Area2D")) { CreateArea2D(); }
				ImGui::TreePop();
			}

			if (m_editorContext->SelectedGameObject.IsValid() && ImGui::MenuItem("Delete object"))
			{
				DestroyObject(m_editorContext->SelectedGameObject);
			}

			ImGui::EndPopup();
		}

		ImGui::End();
	}

	Bambo::GameObject* SceneHierarchyWindow::CreateEmpty()
	{
		return m_editorContext->CurrentWorld->CreateGameObject(m_editorContext->SelectedGameObject);
	}

	void SceneHierarchyWindow::CreateSprite()
	{
		CreateEmpty()->AddComponent<Bambo::SpriteComponent>();
	}

	void SceneHierarchyWindow::CreateText()
	{
		CreateEmpty()->AddComponent<Bambo::TextComponent>();
	}

	void SceneHierarchyWindow::CreateArea2D()
	{
		CreateEmpty()->AddComponent<Bambo::Area2DComponent>();
	}

	bool SceneHierarchyWindow::DestroyObject(Bambo::IID id)
	{
		if (!id.IsValid()) return false;
		if (!m_editorContext->CurrentWorld) return false;

		m_editorContext->CurrentWorld->DestroyGameObject(id);
		m_editorContext->SelectedGameObject = Bambo::IID{};
		g_dragAndDroppedId = Bambo::IID{};
		return true;
	}

	void SceneHierarchyWindow::DisplayChildrenOf(const Bambo::GameObject* gameObject, bool isDisabled, ImGuiTreeNodeFlags additionalFlags)
	{
		const std::vector<Bambo::IID>& children = gameObject->GetChildrenConst();

		for (int i = 0; i < children.size(); ++i)
		{
			Bambo::GameObject* childGo = m_editorContext->CurrentWorld->GetGameObject(children[i]);

			BAMBO_ASSERT_S(childGo)
			BAMBO_ASSERT_S(childGo->IsValid())

			if (childGo->HasProperty(Bambo::GameObject::IsEditorOnly)) continue;

			Bambo::IID id = childGo->GetID();
			std::string& name = childGo->GetName();

			const static ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
			ImGuiTreeNodeFlags nodeFlags = baseFlags | additionalFlags;

			if (childGo->HasProperty(Bambo::GameObject::IsDisabled))
			{
				nodeFlags |= ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Bullet;
			}

			if (id == m_editorContext->SelectedGameObject)
			{
				nodeFlags |= ImGuiTreeNodeFlags_Selected;
			}

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			isDisabled |= childGo->HasProperty(Bambo::GameObject::IsDisabled);
			ImVec4 color = isDisabled ? ColorToImGuiColor(m_internalData.DisabledTextColor) : ColorToImGuiColor(m_internalData.EnabledTextColor);

			ImGui::PushStyleColor(ImGuiCol_Text, color);
			bool isOpened = ImGui::TreeNodeEx((void*)(uintptr_t)id, nodeFlags, name.c_str());

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				m_editorContext->SelectedGameObject = m_editorContext->CurrentWorld->GetGameObject(id)->GetID();
			}

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAutoExpirePayload))
			{
				g_dragAndDroppedId = id;
				ImGui::SetDragDropPayload("GOReparent", &g_dragAndDroppedId, sizeof(Bambo::IID));
				ImGui::Text("%s", name.c_str());
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GOReparent");
				if (payload != nullptr)
				{
					Bambo::IID* goID = static_cast<Bambo::IID*>(payload->Data);
					Bambo::GameObject* targetGo = m_editorContext->CurrentWorld->GetGameObject(*goID);
					targetGo->SetParent(childGo->GetID());
				}

				ImGui::EndDragDropTarget();
			}

			if (!isOpened)
			{
				ImGui::PopStyleColor();
				continue;
			}


			bool noChildren = childGo->GetChildrenCount() == 0;
			DisplayChildrenOf(childGo, isDisabled,  noChildren ? (ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet) : ImGuiBackendFlags_None);

			ImGui::PopStyleColor();
			ImGui::TreePop();
		}
	}

}