#include "Object.h"
#include "Utility.h"
#include "imgui.h"
#include "ConstructUI.h"

namespace staywalk{
	Object::Object(const string& name)
		:guid_(Utility::get_random_id()), name_(name) {
	}
	
	Object::Object(idtype load_id, const string& name)
		: guid_(load_id), name_(name){
	}


	Object::Object(const Object& rhs)
	:guid_(Utility::get_random_id()), name_(rhs.name_) {
	}

	Object::Object(Object&& rhs)
	:guid_(rhs.guid_), name_(rhs.name_){
		rhs.guid_ = kInvalidId;
	}

	Object& Object::operator=(const Object& rhs) {
		guid_ = Utility::get_random_id();
		name_ = rhs.name_;
		return *this;
	}

	Object& Object::operator=(Object&& rhs) {
		guid_ = rhs.guid_;
		name_ = rhs.name_;
		rhs.guid_ = kInvalidId;
		return *this;
	}
	
	void Object::construct_ui(bool can_modify) {
        if (ImGui::BeginTable("##properties", 2, ImGuiTableFlags_Resizable))
        {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 1.0f);
			construct_basic_ui(can_modify);
            ImGui::EndTable();
        }
		construct_obj_ui(can_modify);
	}
}