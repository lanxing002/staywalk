#include "Object.h"

namespace staywalk {

namespace reflect {

	enum class ObjectType : unsigned int {
		None = 0,
		Objct,
		/*{EnumList}*/
	};

	struct MetaInfo{
		ObjectType obj_type;
	};
}

	reflect::MetaInfo Object::get_meta_info() {
		return reflect::MetaInfo{reflect::ObjectType::None};
	}

}




