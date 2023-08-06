#pragma once
#include "Drawers/InspectorDrawer.h"
#include "Core/Essentials.h"

namespace BamboEditor
{
	void DrawInteger(const char* name, int32* value, ImGuiInputTextFlags flags = 0);
	void DrawFloat(const char* name, float* value, ImGuiInputTextFlags flags = 0);
    void DrawString(const char* name, std::string* str, ImGuiInputTextFlags flags = 0);
    void DrawVector3(const char* name, glm::vec3* vec3);
}