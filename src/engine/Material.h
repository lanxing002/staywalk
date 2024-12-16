#pragma once
#include "Common.h"
#include "RProgram.h"

#include <map>


namespace staywalk {
	class sw_Class(jsonpost;)  Material : public Object{
	public:
		sw_Func()  Material(const string& name="0-material");
		sw_Func()  void add_tex(const string & name, Tex2DRef tex);
		sw_Func()  void add_uniform(const string & name, UniformRef uniform);
		sw_Func() bool is_same(MaterialRef rhs);
		sw_Prop() ProgramRef program_;
		MetaRegister(Material);

	public:
		static const string DiffuseKey;
		static const string AoKey;

		~Material();
		void use(RenderInfo info);
		void load_post() { if (program_) Program::monitor(program_, true); }
		void dump_post() const {}

	protected:
		sw_Prop() vector<pair<string, UniformRef>> uniforms_;
		sw_Prop() vector<pair<string, TexRef>> texs_;
	};
}


