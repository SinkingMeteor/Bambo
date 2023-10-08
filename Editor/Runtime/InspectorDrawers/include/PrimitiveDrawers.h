#pragma once
#include "InspectorDrawer.h"
#include "Essentials.h"

namespace BamboEditor
{
	bool DrawInteger(const char* name, int32* value, ImGuiInputTextFlags flags = 0);
	bool DrawUInteger(const char* name, uint32* value, ImGuiInputTextFlags flags = 0);
	bool DrawFloat(const char* name, float* value, ImGuiInputTextFlags flags = 0);
    bool DrawU32String(const char* name, std::u32string* str, ImGuiInputTextFlags flags = 0);
    void DrawString(const char* name, std::string* str, ImGuiInputTextFlags flags = 0);
    void DrawReadonlyString(const std::string* str);
    void DrawVector3(const char* name, glm::vec3* vec3);
}