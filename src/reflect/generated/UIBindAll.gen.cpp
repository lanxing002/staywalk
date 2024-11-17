#include "imgui.h"
#include "Actor.h"

namespace staywalk {
	void Actor::construct_ui() {
		ImGui::Text(name.c_str());
	}
}