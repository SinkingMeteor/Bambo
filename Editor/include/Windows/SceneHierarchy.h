#pragma once
#include "Core/Essentials.h"
#include "EditorEssentials.h"
#include "Windows/GUIWindow.h"
#include "World/World.h"
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

		void DisplayChildrenOf(const Bambo::GameObject* gameObject, ImGuiTreeNodeFlags additionalFlags = ImGuiBackendFlags_::ImGuiBackendFlags_None);
		Bambo::GameObject* CreateEmpty();
		void CreateCamera();
		void CreateSprite();
		bool DestroyObject(Bambo::IID id);
	};
}