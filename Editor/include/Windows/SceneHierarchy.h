#pragma once
#include "Core.h"
#include "Windows/GUIWindow.h"
#include "World/World.h"
#include "imgui.h"
#include "World/Components/Components.h"

namespace BamboEditor
{
	class SceneHierarchyWindow final : public GUIWindow
	{
	public:
		SceneHierarchyWindow(SPtr<Bambo::World> world);
		void OnGUI();
		const std::string& GetWindowName() { return m_windowName; }
	private:
		std::string m_windowName = "Hierarchy";
		SPtr<Bambo::World> m_world;

		void DisplayChildrenOf(Bambo::EntityManager& entityWorld, flecs::entity& entity);
	};
}