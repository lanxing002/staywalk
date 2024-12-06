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
		std::stack<staywalk::mat4> model;
		std::stack<staywalk::mat4> view;
		std::stack<staywalk::mat4> projection;
		staywalk::RProgramRef program{nullptr};
		bool can_override{ false };
	};

}

