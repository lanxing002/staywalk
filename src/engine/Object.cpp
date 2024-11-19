#include "Object.h"
#include "Utility.h"
#include "imgui.h"
#include "ConstructUI.h"

namespace staywalk{
	Object::Object(const string& name)
		:guid_(Utility::get_random_id()), name(name) {
	}
	
	Object::Object(idtype load_id, const string& name)
		: guid_(load_id), name(name){
	}
	
	void Object::construct_ui() {
        if (ImGui::BeginTable("##properties", 2, ImGuiTableFlags_Resizable))
        {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 1.0f);
			construct_basic_ui();
            ImGui::EndTable();
        }
		construct_obj_ui();
	}
}