#pragma once

#include "Object.h"
#include "GameObject.h"


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

	template<typename T, typename Super>
	class Serializer {
	public:
		static ObjectType get_type_value()  { static_assert(false && "Not impl"); }
		static bool operator==(const T& lhs, const T& rhs) {static_assert(false && "Not impl");}

		static void dump(const T& obj, ofstream& ofs, Dumper& dumper) { static_assert(false && "Not impl"); }
		static void load(T& obj, ifstream& ifs, Loader& loader) { static_assert(false && "Not impl"); }
	};
}
}




