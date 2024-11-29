#pragma once
#include "Common.h"

namespace staywalk {
	enum class sw_Class() ProgramType : int {
		PBR,
		Shadow,
		//
		_Count
	};

	struct RenderInfo
	{
		staywalk::mat4 view;
		staywalk::mat4 projection;
		staywalk::RProgramRef program{ nullptr };
		bool can_override{ false };
	};

}

