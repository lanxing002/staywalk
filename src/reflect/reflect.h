#pragma once
#include "Object.h"
#include "Utility.h"

namespace staywalk {
	namespace reflect {
		struct MetaInfo {
			std::string tname;
		};

		shared_ptr<::staywalk::Object> create_empty(MetaInfo minfo);

		template<typename T>
		vector<std::pair<int, string>> get_enum_label();
	}
}

#include "generated/Common.gen.h"
