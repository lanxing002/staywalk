#pragma once
#include "Common.h"
#include "StateSet.h"
#include "RProgram.h"

#include <map>


namespace staywalk {
	class sw_Class(jsonpost;)  Material : public StateSet{
	public:
		sw_Func()  Material(const string& name="0-material");
		sw_Prop() StdProgramRef program_;
		MetaRegister(Material);

	public:
		~Material();
		void use(RenderInfo info);
		void load_post() { if (program_) StdProgram::monitor(program_, true); }
		void dump_post() const {}

	};
}


