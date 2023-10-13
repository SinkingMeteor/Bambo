#pragma once
#include "Essentials.h"
#include "EditorEssentials.h"
#include "GUIWindow.h"
#include "World.h"
#include "Components/Components.h"
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

		void DisplayChildrenOf(const Bambo::GameObject* gameObject, ImGuiTreeNodeFlags additionalFlags = ImGuiBackendFlags_::ImGuiBackendFlags_None);
		Bambo::GameObject* CreateEmpty();
		void CreateCamera();
		void CreateSprite();
		void CreateText();
		void CreateArea2D();
		bool DestroyObject(Bambo::IID id);
	};
}