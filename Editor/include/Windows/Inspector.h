#pragma once
#include "Windows/GUIWindow.h"

namespace BamboEditor
{
	class InspectorWindow : public GUIWindow
	{
	public:
		InspectorWindow();
		virtual void OnGUI() override;
		virtual const std::string& GetWindowName() const override { return m_windowName; }
	private:
		std::string m_windowName;
	};
}