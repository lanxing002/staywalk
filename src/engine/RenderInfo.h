#pragma once
#include "Common.h"
#include <stack>

namespace staywalk {
	enum class sw_Class() ProgramType : int {
		PBR,
		Shadow,
		//
		DeferredPBR,
		DeferredPBRPost,
		_Count
	};

	struct RenderInfo
	{
		std::stack<staywalk::mat4> model_;
		std::stack<staywalk::mat4> view_;
		std::stack<staywalk::mat4> projection_;
		staywalk::StdProgramRef program_{ nullptr };
		staywalk::StateSetRef stateset_{ nullptr };
		int texture_slot = 0;
		bool can_override_{ false };
	};

}

