#pragma once
#include "Object.h"
#include "SimpleType.h"
#include "Utility.h"

namespace staywalk {
	namespace reflect {
		enum class ObjectType :unsigned int;
	}
}

namespace staywalk {
	namespace reflect {
		struct MetaInfo {
			ObjectType otype;  // use for type check and equal operation, dump maybe wrong
			std::string_view tname;
		};

		shared_ptr<::staywalk::Object> create_empty(MetaInfo minfo);

		template<typename T>
		vector<std::pair<int, string>> get_enum_label();
	}
}

#include "generated/Common.gen.h"
