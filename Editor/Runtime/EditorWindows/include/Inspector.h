#pragma once
#include "Essentials.h"
#include "EditorContext.h"
#include "GUIWindow.h"
#include "DefaultDrawers.h"
#include "InspectorDrawersRegistry.h"
namespace BamboEditor
{
	struct InspectorWindowData
	{
		std::string EnabledGameObjectLabel{ "Object is enabled" };
		std::string DisabledGameObjectLabel{ "Object is disabled" };
	};

	class InspectorWindow : public GUIWindow
	{
	public:
		InspectorWindow(EditorContext* editorContext);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName;
		EditorContext* m_editorContext;
		InspectorWindowData m_internalData;
	};
}