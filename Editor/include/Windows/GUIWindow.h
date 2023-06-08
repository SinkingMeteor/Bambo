#pragma once
#include <string>
namespace BamboEditor
{
	class GUIWindow
	{
	public:
		GUIWindow() = default;
		virtual ~GUIWindow() {}

		virtual void OnGUI() = 0;
		virtual const std::string& GetWindowName() const = 0;
	};
}