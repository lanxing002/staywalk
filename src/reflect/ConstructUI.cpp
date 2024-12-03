#include "ConstructUI.h"
#include "Logger.h"
#include "Engine.h"
#include "TextEditor.h"
#include "Event.h"

#include <glm/gtc/quaternion.hpp>

using namespace staywalk;
using namespace staywalk::reflect;

#define TableStartCommon()                                              \
    ImGui::TableNextRow();                                              \
    ImGui::PushID(label.c_str());                                       \
    ImGui::TableNextColumn();                                           \
    ImGui::AlignTextToFramePadding();                                   \
    ImGui::TextUnformatted(fmt::format(" {}   ", label).c_str());       \
    ImGui::TableNextColumn();


#define TableEndCommon()   ImGui::PopID();

template<>
void UIHelper::construct_ui(const string& label, string& data, bool can_modify) {
    TableStartCommon();
    char buffer[256];
    strcpy(buffer, data.c_str());
    ImGui::BeginDisabled(!can_modify);
    if (ImGui::InputText(fmt::format("##{}--", label).c_str(), buffer, IM_ARRAYSIZE(buffer))) {
        auto len = strnlen_s(buffer, 256);
        if (len > 0) {
            data.resize(len);
            strcpy(data.data(), (const char*)buffer);
        }
    }
    ImGui::EndDisabled();
    TableEndCommon();
}

template<>
void UIHelper::construct_ui(const string& label, fs::path& path, bool can_modify) {
    string str = path.u8string();
    construct_ui(label, str, can_modify);
    path = str;
}

template<>
void UIHelper::construct_ui(const string& label, SWCodeRef& code, bool can_modify) {
    TableStartCommon();
    ImGui::BeginDisabled(!can_modify);
    if (ImGui::Button("edit code")) {
        Event::Editor_EditCode(code);
    }
    ImGui::EndDisabled();
    TableEndCommon();
}

template<>
void UIHelper::construct_ui(const string& label, bool& data, bool can_modify) {
    TableStartCommon();
    ImGui::BeginDisabled(!can_modify);
    ImGui::Checkbox(fmt::format("##{}--", label).c_str(), &data);
    ImGui::EndDisabled();
    TableEndCommon();
}

template<>
void UIHelper::construct_ui(const string& label, int& data, bool can_modify) {
    TableStartCommon();
    ImGui::BeginDisabled(!can_modify);
    ImGui::DragInt(fmt::format("##{}--", label).c_str(), &data);
    ImGui::EndDisabled();
    TableEndCommon();
}


template<>
void UIHelper::construct_ui(const string& label, float& data, bool can_modify) {
    TableStartCommon();
    ImGui::BeginDisabled(!can_modify);
    ImGui::DragFloat(fmt::format("##{}--", label).c_str(), &data);
    ImGui::EndDisabled();
    TableEndCommon();
}

template<>
void UIHelper::construct_ui(const string& label, Transform& tf, bool can_modify) {
    UIHelper::construct_ui<vec3>("position", tf.location, can_modify);
    UIHelper::construct_ui<vec3>("scale", tf.scale, can_modify);
    UIHelper::construct_ui<quat>("rotation", tf.rotation, can_modify);
}

template<>
void UIHelper::construct_ui(const string& label, vec3& tf, bool can_modify) {
    TableStartCommon();
    ImGui::BeginDisabled(!can_modify);
    ImGui::DragFloat3(fmt::format("##{}--", label).c_str(), &tf.x);
    ImGui::EndDisabled();
    TableEndCommon();
}


template<>
void UIHelper::construct_ui(const string& label, quat& q, bool can_modify) {
    TableStartCommon();
    glm::vec3 euler = glm::degrees(glm::eulerAngles(q));
    ImGui::BeginDisabled(!can_modify);
    if (ImGui::DragFloat3(fmt::format("##{}--", label).c_str(), &euler.x)) {
        q = glm::quat(glm::radians(euler));
    }
    ImGui::EndDisabled();
    TableEndCommon();
}

void UIHelper::construct_enum_ui(const string& label, int& data, const std::vector<std::pair<int, std::string>>& enum_labels, bool can_modify) {
    TableStartCommon();

    std::string choice_lable = "--Error--";
    for (auto [idx, l] : enum_labels)
        if (idx == data) choice_lable = l;

    ImGui::BeginDisabled(!can_modify);
    if (ImGui::BeginCombo(fmt::format("##combox{}", label).c_str(), choice_lable.c_str())) {
        for (int n = 0; n < enum_labels.size(); n++) {
            const bool is_selected = (enum_labels[n].first == data);
            if (ImGui::Selectable(enum_labels[n].second.c_str(), is_selected))
                data = enum_labels[n].first;
            
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::EndDisabled();
    TableEndCommon();
}

