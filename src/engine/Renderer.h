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

		virtual void initialize();

		virtual void destroy();

		virtual void render(double delta, unsigned long long count);

	protected:
		StateSetRef stateset_;
		std::array<ProgramRef, (int)ProgramType::_Count> program_table_;

		string pbr_name_ = "pbr";
		string shadow_name_ = "shadow";
	};
}