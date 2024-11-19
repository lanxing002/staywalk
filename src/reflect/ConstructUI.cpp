#include "ConstructUI.h"
#include "Logger.h"

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
void UIHelper::construct_ui(const string& label, fs::path& path) {
    string str = path.u8string();
    construct_ui(label, str);
    path = str;
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

template<>
void UIHelper::construct_ui(const string& label, Transform& tf) {
    UIHelper::construct_ui<vec3>("position", tf.location);
    UIHelper::construct_ui<vec3>("scale", tf.scale);
    UIHelper::construct_ui<quat>("rotation", tf.rotation);
}

template<>
void UIHelper::construct_ui(const string& label, vec3& tf) {
    TableStartCommon();
    ImGui::DragFloat3(fmt::format("##{}--", label).c_str(), &tf.x);
    TableEndCommon();
}


template<>
void UIHelper::construct_ui(const string& label, quat& q) {
    TableStartCommon();
    glm::vec3 euler = glm::degrees(glm::eulerAngles(q));
    if (ImGui::DragFloat3(fmt::format("##{}--", label).c_str(), &euler.x)) {
        q = glm::quat(glm::radians(euler));
    }

    TableEndCommon();
}
