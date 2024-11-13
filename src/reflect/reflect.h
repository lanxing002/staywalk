#pragma once
#include "Object.h"
#include "Utility.h"

namespace staywalk {
	namespace reflect {
		struct MetaInfo {
			std::string_view tname;
		};

		shared_ptr<::staywalk::Object> create_empty(MetaInfo minfo);
	}
}

#include "generated/Common.gen.h"
