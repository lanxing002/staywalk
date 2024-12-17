#pragma once
#include "Common.h"
#include "RenderInfo.h"
#include "RenderObject.h"

namespace staywalk {
	class Renderer {
	public:
		Renderer() {}
		~Renderer();

		ProgramRef query_program(ProgramType pt);

		void initialize();

		void destroy();

		virtual void render(double delta, unsigned long long count);

	private:
		RenderLight light_mgr_;
		StateSetRef stateset_;
		std::array<ProgramRef, (int)ProgramType::_Count> program_table_;
	};
}