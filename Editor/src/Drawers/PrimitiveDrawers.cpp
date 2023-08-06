#include "Drawers/PrimitiveDrawers.h"

namespace BamboEditor
{
    void DrawInteger(const char* name, int32* value, ImGuiInputTextFlags flags)
    {
        ImGui::InputInt(name, value, 1, 100, flags);
    }

    void DrawFloat(const char* name, float* value, ImGuiInputTextFlags flags)
    {
        ImGui::InputFloat(name, value, 1, 100, "%.3f", flags);
    }

    struct InputTextCallback_UserData
    {
        std::string* Str;
    };

    static int InputTextCallback(ImGuiInputTextCallbackData* data)
    {
        InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
        std::string* str = user_data->Str;
        BAMBO_ASSERT_S(data->Buf == str->c_str());
        str->resize(data->BufTextLen);
        data->Buf = (char*)str->c_str();
        return 0;
    }

    void DrawString(const char* name, std::string* str, ImGuiInputTextFlags flags)
    {
        InputTextCallback_UserData cb_user_data{};
        cb_user_data.Str = str;

        ImGui::InputText(name, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
    }

    void DrawVector3(const char* name, glm::vec3* vec3)
    {
        ImGui::InputFloat3(name, glm::value_ptr(*vec3));
    }
}