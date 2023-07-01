#pragma once
#include "Core.h"
#include "Windows/GUIWindow.h"
#include "World/World.h"
#include "imgui.h"
#include "World/Components/Components.h"
#include "EditorContext.h"

namespace BamboEditor
{
	class SceneHierarchyWindow final : public GUIWindow
	{
	public:
		SceneHierarchyWindow(EditorContext* editorContext);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName = "Hierarchy";
		EditorContext* m_editorContext;
		Bambo::Entity* m_selectedEntity;

		void DisplayChildrenOf(Bambo::EntityManager& entityWorld, flecs::entity& entity, ImGuiTreeNodeFlags additionalFlags = ImGuiBackendFlags_::ImGuiBackendFlags_None);
		Bambo::Entity& CreateEmpty();
		void CreateCamera();
	};
}