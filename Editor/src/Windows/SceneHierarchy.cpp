#include "Windows/SceneHierarchy.h"

namespace BamboEditor
{
	SceneHierarchyWindow::SceneHierarchyWindow(SPtr<Bambo::World> world) :
		m_windowName("Hierarchy"),
		m_world(world)
	{}

	void SceneHierarchyWindow::OnGUI()
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_None;
		flags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;

		ImGui::Begin(m_windowName.c_str(), nullptr, flags);

		if (!m_world)
		{
			ImGui::End();
			return;
		}


		flecs::entity& rootEntity = m_world->GetRoot().GetInternalEntity();
		Bambo::EntityManager& entityWorld = m_world->GetEntityManager();
		DisplayChildrenOf(entityWorld, rootEntity);

		ImGui::End();
	}

	void SceneHierarchyWindow::DisplayChildrenOf(Bambo::EntityManager& entityWorld, flecs::entity& entity)
	{
		ecs_iter_t it = ecs_children(entityWorld, entity);

		while (ecs_children_next(&it))
		{
			for (int i = 0; i < it.count; ++i)
			{
				ecs_entity_t child = it.entities[i];
				flecs::entity childEntity = entityWorld.entity(child);

				BAMBO_ASSERT_S(childEntity.has<Bambo::TagComponent>());

				const Bambo::TagComponent* tag = childEntity.get<Bambo::TagComponent>();

				if (ImGui::TreeNode(tag->Tag.c_str()))
				{
					DisplayChildrenOf(entityWorld, childEntity);
					ImGui::TreePop();
				}

			}
		}
	}

}