#pragma once

#include "Object.h"
#include "GameObject.h"


namespace staywalk {

namespace reflect {

	enum class ObjectType : unsigned int {
		None = 0,
		Objct,
		GameObject,
		/*{EnumList}*/
	};

	struct MetaInfo{
		ObjectType obj_type;
	};
}

	reflect::MetaInfo Object::get_meta_info() {
		return reflect::MetaInfo{reflect::ObjectType::Objct};
	}

	reflect::MetaInfo GameObject::get_meta_info() {
		return reflect::MetaInfo{ reflect::ObjectType::GameObject };
	}
}




