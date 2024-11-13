#pragma once
#include "Object.h"
#include "Utility.h"

namespace staywalk {
	namespace reflect {
		enum class ObjectType : unsigned int;

		struct MetaInfo {
			ObjectType obj_type;
		};
	}
}

#include "Common.gen.h"
