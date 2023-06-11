#pragma once
#include <string>
#include "Project.h"
namespace BamboEditor
{
	class GUIWindow
	{
	public:
		GUIWindow() = default;
		virtual ~GUIWindow() {}

		virtual void OnGUI() = 0;
		virtual const std::string& GetWindowName() const = 0;
		virtual void OnProjectChanged(const Project& project) {}
	};
}