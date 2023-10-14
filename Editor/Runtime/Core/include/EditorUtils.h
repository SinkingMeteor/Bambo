#pragma once
#include "imgui.h"
#include "Essentials.h"

namespace BamboEditor
{
	inline ImVec4 ColorToImGuiColor(const Bambo::Color& color) { return ImVec4{ color.R, color.G, color.B, color.A }; }
}