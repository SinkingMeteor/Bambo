#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"
#include "GUIWindow.h"
#include "World.h"
#include "Components/Components.h"
#include "EditorContext.h"

namespace BamboEditor
{
	struct SceneHierarchyWindowData
	{
		Bambo::Color DisabledTextColor{ Bambo::Color::Red() };
		Bambo::Color EnabledTextColor{ Bambo::Color::White() };
	};

	class SceneHierarchyWindow final : public GUIWindow
	{
	public:
		SceneHierarchyWindow(EditorContext* editorContext);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName = "Hierarchy";
		EditorContext* m_editorContext;
		SceneHierarchyWindowData m_internalData;

		void DisplayChildrenOf(const Bambo::GameObject* gameObject, bool isDisabled, ImGuiTreeNodeFlags additionalFlags = 0);
		Bambo::GameObject* CreateEmpty();

		void CreateSprite();
		void CreateText();
		void CreateArea2D();

		bool DestroyObject(Bambo::IID id);
	};
}