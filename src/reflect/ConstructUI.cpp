#include "ConstructUI.h"
#include "Logger.h"

using namespace staywalk;
using namespace staywalk::reflect;

#define TableStartCommon()                                              \
    ImGui::TableNextRow();                                              \
    ImGui::PushID(label.c_str());                                       \
    ImGui::TableNextColumn();                                           \
    ImGui::AlignTextToFramePadding();                                   \
    ImGui::TextUnformatted(fmt::format(" {} ", label).c_str());    \
    ImGui::TableNextColumn();


#define TableEndCommon()   ImGui::PopID();

template<>
void UIHelper::construct_ui(const string& label, string& data) {
    TableStartCommon();
    char buffer[256];
    strcpy(buffer, data.c_str());
    if (ImGui::InputText(fmt::format("##{}--", label).c_str(), buffer, IM_ARRAYSIZE(buffer))) {
        auto len = strnlen_s(buffer, 256);
        if (len > 0) {
            data.resize(len);
            strcpy(data.data(), (const char*)buffer);
        }
    }
    TableEndCommon();
}

template<>
void UIHelper::construct_ui(const string& label, bool& data) {
    TableStartCommon();
    ImGui::Checkbox(fmt::format("##{}--", label).c_str(), &data);
    ImGui::PopID();
    TableEndCommon();
}

template<>
void UIHelper::construct_ui(const string& label, int& data) {
    TableStartCommon();
    ImGui::DragInt(fmt::format("##{}--", label).c_str(), &data);
    TableEndCommon();
}


template<>
void UIHelper::construct_ui(const string& label, float& data) {
    TableStartCommon();
    ImGui::DragFloat(fmt::format("##{}--", label).c_str(), &data);
    TableEndCommon();
}