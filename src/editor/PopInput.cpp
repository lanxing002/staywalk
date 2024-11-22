#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <string>
#include "PopInput.h"

long long PopTextInput::PopId = 1212;

PopTextInput::PopTextInput(const std::string& label, const std::string& str)
    :label_(label), popId_("__PopTextInput" + std::to_string(PopId++)) {
}

PopTextInput::~PopTextInput(){
}

void PopTextInput::draw(){
    ImGui::OpenPopup(popId_.c_str());
    if (ImGui::BeginPopupModal(popId_.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        char buffer[1024];
        memcpy(buffer, text_.c_str(), text_.size());
        ImGui::Text(label_.c_str());
        ImGui::InputText("##Input", buffer, IM_ARRAYSIZE(buffer));
        auto len = strlen(buffer);
        text_.resize(len);
        strcpy(text_.data(), buffer);

        if (ImGui::Button("OK", ImVec2(120, 0))) {
            done_ = true;
            if (ok_callback) ok_callback(text_);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            done_ = true;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

bool PopTextInput::finished() const
{
    return done_;
}
