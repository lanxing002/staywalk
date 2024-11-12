#pragma once

#include "Object.h"
#include "GameObject.h"
#include "Utility.h"


// 1. dump and load
// 2. register ObjectType
// 3. get_meta_info function

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
}




