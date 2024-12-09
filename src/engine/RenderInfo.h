#pragma once
#include "Common.h"
#include <stack>

namespace staywalk {
	enum class sw_Class() ProgramType : int {
		PBR,
		Shadow,
		//
		_Count
	};

	struct RenderInfo
	{
		std::stack<staywalk::mat4> model_;
		std::stack<staywalk::mat4> view_;
		std::stack<staywalk::mat4> projection_;
		staywalk::RProgramRef program_{nullptr};
		bool can_override_{ false };
	};

}

