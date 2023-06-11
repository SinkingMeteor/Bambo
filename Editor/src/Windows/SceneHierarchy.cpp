#include "Windows/SceneHierarchy.h"

namespace BamboEditor
{
	SceneHierarchyWindow::SceneHierarchyWindow(SPtr<Bambo::World> world) :
		m_windowName("Hierarchy"),
		m_world(world),
		m_selectedEntity(nullptr)
	{}

	void SceneHierarchyWindow::OnGUI()
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysVerticalScrollbar;

		ImGui::Begin(m_windowName.c_str(), nullptr, flags);

		if (!m_world)
		{
			ImGui::End();
			return;
		}

		if (ImGui::IsItemClicked())
		{
			m_selectedEntity = nullptr;
		}

		flecs::entity& rootEntity = m_world->GetRoot().GetInternalEntity();
		Bambo::EntityManager& entityWorld = m_world->GetEntityManager();
		DisplayChildrenOf(entityWorld, rootEntity);

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

	Bambo::Entity& SceneHierarchyWindow::CreateEmpty()
	{
		if (!m_selectedEntity)
		{
			return m_world->CreateEntity();
		}
	
		return m_world->CreateEntity(m_selectedEntity->GetID());
	}

	void SceneHierarchyWindow::CreateCamera()
	{
		CreateEmpty().AddComponent<Bambo::CameraComponent>();
	}

	void SceneHierarchyWindow::DisplayChildrenOf(Bambo::EntityManager& entityWorld, flecs::entity& entity, ImGuiTreeNodeFlags additionalFlags)
	{
		ecs_iter_t it = ecs_children(entityWorld, entity);

		while (ecs_children_next(&it))
		{
			for (int i = 0; i < it.count; ++i)
			{
				ecs_entity_t child = it.entities[i];
				flecs::entity childEntity = entityWorld.entity(child);

				if (!childEntity.has<Bambo::TagComponent>()) continue;

				const Bambo::TagComponent* tag = childEntity.get<Bambo::TagComponent>();
				const Bambo::IDComponent* idComponent = childEntity.get<Bambo::IDComponent>();

				static ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
				ImGuiTreeNodeFlags nodeFlags = baseFlags;

				nodeFlags |= additionalFlags;

				if (m_selectedEntity != nullptr && m_selectedEntity->GetID() == idComponent->ID)
				{
					nodeFlags |= ImGuiTreeNodeFlags_Selected;
				}

				if (ImGui::TreeNodeEx((void*)(uintptr_t)idComponent->ID, nodeFlags, tag->Tag.c_str()))
				{
					if(ImGui::IsItemClicked())
					{
						m_selectedEntity = &m_world->GetEntityByID(idComponent->ID);
					}

					if (ImGui::BeginDragDropSource())
					{
						ImGui::SetDragDropPayload("GOReparent", &childEntity, sizeof(childEntity));
						ImGui::Text("%s", tag->Tag.c_str());
						ImGui::EndDragDropSource();
					}

					if (ImGui::BeginDragDropTarget())
					{
						 const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GOReparent");
						 if(payload != nullptr)
						 {
							 flecs::entity* targetEntity = static_cast<flecs::entity*>(payload->Data);
							 targetEntity->child_of(childEntity);
						 }

						 ImGui::EndDragDropTarget();
					}

					bool noChildren = ecs_children(entityWorld, childEntity).count == 0;
					DisplayChildrenOf(entityWorld, childEntity, noChildren ? ImGuiBackendFlags_None : ImGuiTreeNodeFlags_Leaf);
					ImGui::TreePop();
				}
			}
		}
	}

}