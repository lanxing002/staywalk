#pragma once
#include "Common.h"
#include "RenderInfo.h"
#include "RenderObject.h"

namespace staywalk {
	class Renderer {
	public:
		Renderer() {}
		~Renderer() {}

		RProgramRef query_program(ProgramType pt);

		void initialize();

		virtual void render(double delta, unsigned long long count);

	private:
		RLight light_mgr_;
		std::array<RProgramRef, (int)ProgramType::_Count> program_table_;
	};
}