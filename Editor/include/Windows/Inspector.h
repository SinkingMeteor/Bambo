#pragma once
#include "Core/Essentials.h"
#include "EditorContext.h"
#include "Windows/GUIWindow.h"

namespace BamboEditor
{
	class InspectorWindow : public GUIWindow
	{
	public:
		InspectorWindow(EditorContext* editorContext);
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName;
		EditorContext* m_editorContext;
	};
}