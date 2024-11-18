#include "imgui.h"
#include "Actor.h"

namespace staywalk {
    void Actor::ui_help()
    {
        ImGui::TableNextRow();
        ImGui::PushID("name");
        ImGui::TableNextColumn();
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted(" name ");
        ImGui::TableNextColumn();

        char buffer[256];
        strcpy(buffer, name.c_str());
        if (ImGui::InputText("##name-", buffer, IM_ARRAYSIZE(buffer))) {
            auto len = strnlen_s(buffer, 256);
            name.resize(len);
            strcpy(name.data(), (const char*)buffer);
        }
        ImGui::PopID();

    }
    void Actor::construct_ui() {
        if (ImGui::CollapsingHeader("Basic", ImGuiTreeNodeFlags_DefaultOpen)) {
            //ImGui::Separator();
            
            if (ImGui::BeginTable("##properties", 2, ImGuiTableFlags_Resizable /*| ImGuiTableFlags_ScrollY*/))
            {
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 2.0f);
                {
                    ui_help();
                    ////static bool aa;
                    ////ImGui::Checkbox("##Editor", &aa);
                    ////ImGui::PopID();

                    ////void* field_ptr = (void*)(((unsigned char*)node) + field_desc.Offset);
                    //auto dtype2 = ImGuiDataType_S32;
                    ////IM_ASSERT(field_desc.DataCount == 1);
                    //static int vv;
                    //ImGui::DragInt("##Editor", &vv);

                }
                ImGui::EndTable();
            }
        }

        //if (ImGui::CollapsingHeader("Comp-test"))
        //{
        //    if (ImGui::TreeNode("TE")) {
        //        if (ImGui::TreeNode("TE2")) {
        //            if (ImGui::CollapsingHeader("Comp-test")) {
        //                if (ImGui::TreeNode("Tee")) {
        //                    ImGui::TreePop();
        //                }
        //            }
        //            ImGui::TreePop();
        //        }
        //        ImGui::TreePop();
        //    }
        //}
	}
}