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
}