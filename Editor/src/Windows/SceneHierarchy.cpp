#include "Windows/SceneHierarchy.h"

namespace BamboEditor
{
	SceneHierarchyWindow::SceneHierarchyWindow(EditorContext* editorContext) :
		m_windowName("Hierarchy"),
		m_editorContext(editorContext)
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
			m_editorContext->SelectedGameObject = Bambo::IID{};
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
				if (ImGui::MenuItem("Sprite")) { CreateSprite(); }
				ImGui::TreePop();
			}
			ImGui::EndPopup();
		}

		ImGui::End();
	}

	Bambo::GameObject* SceneHierarchyWindow::CreateEmpty()
	{
		return m_editorContext->CurrentWorld->CreateGameObject(m_editorContext->SelectedGameObject);
	}

	void SceneHierarchyWindow::CreateCamera()
	{
		CreateEmpty()->AddComponent<Bambo::CameraComponent>();
	}

	void SceneHierarchyWindow::CreateSprite()
	{
		CreateEmpty()->AddComponent<Bambo::SpriteComponent>();
	}

	void SceneHierarchyWindow::DisplayChildrenOf(const Bambo::GameObject* gameObject, ImGuiTreeNodeFlags additionalFlags)
	{
		const std::vector<Bambo::IID>& children = gameObject->GetChildrenConst();

		for (int i = 0; i < children.size(); ++i)
		{
			Bambo::GameObject* childGo = m_editorContext->CurrentWorld->GetGameObject(children[i]);

			BAMBO_ASSERT_S(childGo)
			BAMBO_ASSERT_S(childGo->IsValid())

			Bambo::IID id = childGo->GetID();
			std::string& name = childGo->GetName();

			const static ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;
			ImGuiTreeNodeFlags nodeFlags = baseFlags | additionalFlags;

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			if (ImGui::TreeNodeEx((void*)(uintptr_t)id, nodeFlags, name.c_str()))
			{
				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					//@TODO: To inspector window
					m_editorContext->SelectedGameObject = m_editorContext->CurrentWorld->GetGameObject(id)->GetID();
				}

				if (ImGui::BeginDragDropSource())
				{
					ImGui::SetDragDropPayload("GOReparent", &*childGo, sizeof(*childGo));
					ImGui::Text("%s", name.c_str());
					ImGui::EndDragDropSource();
				}

				if (ImGui::BeginDragDropTarget())
				{
						const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GOReparent");
						if(payload != nullptr)
						{
							Bambo::GameObject* targetGo = static_cast<Bambo::GameObject*>(payload->Data);
							targetGo->SetParent(childGo->GetID());
						}

						ImGui::EndDragDropTarget();
				}

				bool noChildren = childGo->GetChildrenCount() == 0;
				DisplayChildrenOf(childGo, noChildren ? (ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet) : ImGuiBackendFlags_None);
				ImGui::TreePop();
			}
		}
	}

}