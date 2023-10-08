#include "PrimitiveDrawers.h"

namespace BamboEditor
{
    bool DrawInteger(const char* name, int32* value, ImGuiInputTextFlags flags)
    {
        int32 iVal = *value;
        ImGui::InputInt(name, &iVal, 1, 100, flags);

        if (iVal != *value)
        {
            *value = iVal;
            return true;
        }
        return false;
    }

    bool DrawUInteger(const char* name, uint32* value, ImGuiInputTextFlags flags)
    {
        int32 iVal = static_cast<int32>(*value);
        ImGui::InputInt(name, &iVal, 1, 100, flags);
        if (iVal != *value)
        {
            iVal = std::max(0, iVal);
            *value = static_cast<uint32>(iVal);

            return true;
        }
        return false;
    }

    bool DrawFloat(const char* name, float* value, ImGuiInputTextFlags flags)
    {
        float iVal = *value;
        ImGui::InputFloat(name, &iVal, 1, 100, "%.3f", flags);
        if (iVal != *value)
        {
            *value = iVal;
            return true;
        }
        return false;
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
        InputTextCallback_UserData callbackData{};
        callbackData.Str = str;

        ImGui::InputText(name, (char*)str->c_str(), str->capacity() + 1, flags | ImGuiInputTextFlags_CallbackResize, InputTextCallback, &callbackData);
    }

    bool DrawU32String(const char* name, std::u32string* str32, ImGuiInputTextFlags flags)
    {
        InputTextCallback_UserData callbackData{};

        std::string str = Bambo::ToUtf8(*str32);
        callbackData.Str = &str;

        ImGui::InputText(name, (char*)str.c_str(), str.capacity() + 1, flags | ImGuiInputTextFlags_CallbackResize, InputTextCallback, &callbackData);

        std::u32string newVal = Bambo::ToUtf32(str);

        if (newVal != *str32)
        {
            *str32 = newVal;
            return true;
        }

        return false;
    }


    void DrawReadonlyString(const std::string* str)
    {
        ImGui::TextWrapped(str->c_str());
    }

    void DrawVector3(const char* name, glm::vec3* vec3)
    {
        ImGui::InputFloat3(name, glm::value_ptr(*vec3));
    }
}